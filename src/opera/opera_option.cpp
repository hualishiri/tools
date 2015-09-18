#include "opera/opera_option.h"

#include <assert.h>

#include <algorithm>
#include <set>
#include <sstream>

#include "util/tool.h"
#include "util/logger.h"

namespace tools {

OperaOption* OperaOption::opera_option_ = 0;

OperaOption* OperaOption::Instance() {
  if (opera_option_ == 0)
    opera_option_ = new OperaOption();
  return opera_option_;
}


void OperaOption::push_back_radar(Radar& radar) {
  assert(radar.id > 0);
  assert(radar.type == R_STATIC || radar.type == R_DYNAMIC);
  assert(ValidOfLongitude(radar.start_x));
  assert(ValidOfLatitude(radar.start_y));
  assert(ValidOfLongitude(radar.radius_x));
  assert(ValidOfLatitude(radar.radius_y));
  for (std::size_t i=0; i!=radar.azimuth_range.size(); ++i) {
    assert(ValidOfCircleAngle(radar.azimuth_range[i].first));
    assert(ValidOfCircleAngle(radar.azimuth_range[i].second));
  }

  if (radar.type == R_STATIC) {
    radar.track_id = 0;
  } 
  if (radar.type == R_DYNAMIC){
    assert(IsIDExistInTrackSet(radar.track_id));
  }
  assert(((~(AIRCRAFT | LANDCRAFT | UNDERCRAFT)) & 
      radar.detecting_objects_types) == 0x0);
  radars_.push_back(radar);

  assert(IsIDUnique());
}

void OperaOption::pop_radar(long long id) {
  std::vector<Radar>::iterator iter = radars_.begin();
  for (; iter != radars_.end(); ++iter) {
    if (iter->id == id) {
      radars_.erase(iter);
      return;
    }
  }
}

void OperaOption::push_back_track(Track& track) {
  assert(track.lines.size() + track.circles.size() == track.types.size());
  assert(track.ids.size() == static_cast<std::size_t>(track.batch_count));
  assert(track.level_noise_track >= 0.0 && track.level_noise_track <= 256);
  assert(track.id >= 0);
  for (std::size_t i = 0; i != track.start_speeds.size(); ++i)
    assert(track.start_speeds[i] >= 0.0 && track.start_speeds[i] <= 10);
  tracks_.push_back(track); 
  assert(track.accelerations.size() == 
      static_cast<std::size_t>(track.batch_count));
  for (std::size_t i=0; i!= track.accelerations.size(); ++i )
    assert(track.accelerations[i].size() == track.types.size());
  assert(track.track_types.size() == 
      static_cast<std::size_t>(track.batch_count));
  for (std::size_t i=0; i!=track.track_types.size(); ++i) {
    assert(((~(AIRCRAFT | LANDCRAFT | UNDERCRAFT)) & 
        track.track_types[i]) == 0x00);
  }
  assert(IsIDUnique());
}

void OperaOption::ConvertToPixel() {
  for (std::size_t i=0; i!=radars_.size(); ++i) {
    FromWgsToPixel(&radars_[i].start_x, &radars_[i].start_y);
    FromWgsToPixel(&radars_[i].radius_x, &radars_[i].radius_y);
  }  
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    for (std::size_t j=0; j!=tracks_[i].lines.size(); ++j) {
      FromWgsToPixel(&tracks_[i].lines[j].start_x,
                     &tracks_[i].lines[j].start_y);
      FromWgsToPixel(&tracks_[i].lines[j].end_x,
                     &tracks_[i].lines[j].end_y);
    }
    for (std::size_t j=0; j!=tracks_[i].circles.size(); ++j) {
      FromWgsToPixel(&tracks_[i].circles[j].start_x,
                     &tracks_[i].circles[j].start_y);
      FromWgsToPixel(&tracks_[i].circles[j].center_x,
                     &tracks_[i].circles[j].center_y);
    }
  }
}

void OperaOption::ConvertToPlaneCoodinate(void (*Conv)(double*, double*)) {
  for (std::size_t i=0; i!=radars_.size(); ++i) {
    Conv(&radars_[i].start_x, &radars_[i].start_y);
    Conv(&radars_[i].radius_x, &radars_[i].radius_y);
  }  
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    for (std::size_t j=0; j!=tracks_[i].lines.size(); ++j) {
      Conv(&tracks_[i].lines[j].start_x,
                     &tracks_[i].lines[j].start_y);
      Conv(&tracks_[i].lines[j].end_x,
                     &tracks_[i].lines[j].end_y);
    }
    for (std::size_t j=0; j!=tracks_[i].circles.size(); ++j) {
      Conv(&tracks_[i].circles[j].start_x,
                     &tracks_[i].circles[j].start_y);
      Conv(&tracks_[i].circles[j].center_x,
                     &tracks_[i].circles[j].center_y);
    }
  }
}

std::vector<OperaOption::TrackInternal> OperaOption::tracks() const { 
  std::vector<TrackInternal> track_internals;
  std::size_t track_batch_count = 0;
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    track_batch_count = static_cast<std::size_t>(tracks_[i].batch_count);
    for (std::size_t j=0; j!=track_batch_count; ++j) {
      TrackInternal track_internal = {
        tracks_[i].ids[j],
        tracks_[i].start_speeds[j],
        tracks_[i].accelerations[j],
        tracks_[i].time_delays[j],
        tracks_[i].track_types[j],
        tracks_[i].lines,
        tracks_[i].circles,
        tracks_[i].types
      };
      if (0 != j)
        TrackInternalSift(track_internal, tracks_[i].level_noise_track, j);
      track_internals.push_back(track_internal);
    }
  }
  return track_internals;
}

void OperaOption::TrackInternalSift(TrackInternal& track_internal,
                                    double level_noise,
                                    int seed) const{
  double x_sift = GetRandNumber(seed + 1) * level_noise / 200.0;
  double y_sift = GetRandNumber(seed + 2) * level_noise / 200.0;
  for (std::size_t i=0; i!=track_internal.lines.size(); ++i) {
    track_internal.lines[i].start_x += x_sift;
    track_internal.lines[i].start_y += y_sift;
    track_internal.lines[i].end_x += x_sift;
    track_internal.lines[i].end_y += y_sift;
  }
  for (std::size_t i=0; i!=track_internal.circles.size(); ++i) {
    track_internal.circles[i].start_x += x_sift;
    track_internal.circles[i].start_y += y_sift;
    track_internal.circles[i].center_x+= x_sift;
    track_internal.circles[i].center_y += y_sift;
  }
}

std::ostream& operator<< (std::ostream& os, const OperaOption& op) {
  os << op.radars_.size() << std::endl;
  for (std::size_t i=0; i!=op.radars_.size(); ++i) {
    os << op.radars_[i].id << " "
        << op.radars_[i].type << " " 
        << op.radars_[i].start_x << " "   
        << op.radars_[i].start_y << " "   
        << op.radars_[i].radius_x << " "   
        << op.radars_[i].radius_y << " "   
        << op.radars_[i].detecting_objects_types << " "
        << op.radars_[i].error.error_random_azimuth << " "   
        << op.radars_[i].error.error_random_distance << " "   
        << op.radars_[i].error.error_random_elevation << " "
        << op.radars_[i].error.error_system_azimuth << " "
        << op.radars_[i].error.error_system_distance << " "
        << op.radars_[i].error.error_system_elevation << " ";

    os << op.radars_[i].azimuth_range.size() << " ";
    for (std::size_t j=0; j!=op.radars_[i].azimuth_range.size(); ++j) {
      os << op.radars_[i].azimuth_range[j].first << " ";
      os << op.radars_[i].azimuth_range[j].second << " ";
    }
  }
  os << op.tracks_.size() << " ";
  for (std::size_t i=0; i!=op.tracks_.size(); ++i) {
    os << op.tracks_[i].id << " ";
    os << op.tracks_[i].reserve.type << " ";
    os << op.tracks_[i].batch_count << " ";
    os << op.tracks_[i].level_noise_track << " ";

    os << op.tracks_[i].start_speeds.size() << " ";
    
    for (std::size_t j=0; j!=op.tracks_[i].start_speeds.size(); ++j) {
      os << op.tracks_[i].start_speeds[j] << " "
         << op.tracks_[i].time_delays[j] << " "
         << op.tracks_[i].ids[j] << " ";

      os << op.tracks_[i].accelerations[j].size() << " ";
      for (std::size_t k=0; k!=op.tracks_[i].accelerations[j].size(); ++k)
         os << op.tracks_[i].accelerations[j][k] << " ";
    }

    int line_index = 0, circle_index = 0;
    os << op.tracks_[i].types.size() << " ";
    for (std::size_t j=0; j!=op.tracks_[i].types.size(); ++j) {
      if (OperaOption::LINE == op.tracks_[i].types[j]) {
        os << 0<< " "
            << op.tracks_[i].lines[line_index].id << " "
            << op.tracks_[i].lines[line_index].start_x << " "
            << op.tracks_[i].lines[line_index].start_y << " "
            << op.tracks_[i].lines[line_index].end_x << " "
            << op.tracks_[i].lines[line_index].end_y << " ";
        ++line_index;
      } else if (OperaOption::CIRCLE == op.tracks_[i].types[j]) {
        os << 1 << " "
            << op.tracks_[i].circles[circle_index].id << " "
            << op.tracks_[i].circles[circle_index].start_x << " "
            << op.tracks_[i].circles[circle_index].start_y << " "
            << op.tracks_[i].circles[circle_index].center_x << " "
            << op.tracks_[i].circles[circle_index].center_y << " "
            << op.tracks_[i].circles[circle_index].angle << " ";
      }
    }

    os << op.tracks_[i].track_types.size() << " "; 
    for (std::size_t j=0; j!=op.tracks_[i].track_types.size(); ++j)
      os << op.tracks_[i].track_types[j] << " ";
  }
  return os;
}
    
std::istream& operator>> (std::istream& in, OperaOption& op) {
  op.radars_.clear();
  op.tracks_.clear();
  std::size_t size_radar;
  in >> size_radar;
  for (std::size_t i=0; i!=size_radar; ++i) {
    OperaOption::Radar radar;
    in >> radar.id
        >> radar.type
        >> radar.start_x
        >> radar.start_y
        >> radar.radius_x
        >> radar.radius_y
        >> radar.detecting_objects_types
        >> radar.error.error_random_azimuth
        >> radar.error.error_random_distance
        >> radar.error.error_random_elevation
        >> radar.error.error_system_azimuth
        >> radar.error.error_system_distance
        >> radar.error.error_system_elevation;

    std::size_t size_azimuth_range = 0;
    in >> size_azimuth_range;
    double angle_azimuth;
    double angle_sector_range;
    for (std::size_t j=0; j!=size_azimuth_range; ++j) {
      in >> angle_azimuth
          >> angle_sector_range;
      radar.azimuth_range.push_back(
          std::make_pair(angle_azimuth, angle_sector_range));
    }
    op.push_back_radar(radar); 
  }

  std::size_t size_track;
  in >> size_track;
  OperaOption::Track track;
  for (std::size_t i=0; i!=size_track; ++i) {
    track.start_speeds.clear();
    track.accelerations.clear();
    track.time_delays.clear();
    track.ids.clear();
    track.circles.clear();
    track.lines.clear();
    track.types.clear();
    track.track_types.clear();
    
    in >> track.id;
    in >> track.reserve.type;
    in >> track.batch_count;
    in >> track.level_noise_track;

    std::size_t size_ids;
    in >> size_ids;

    double temp;
    for (std::size_t j=0; j!=size_ids; ++j) {
      in >> temp;
      track.start_speeds.push_back(temp);
      in >> temp;
      track.time_delays.push_back(temp);
      in >> temp;
      track.ids.push_back(static_cast<long long>(temp));

      float acc = 0.0f;
      size_t size_accele;
      in >> size_accele;
      std::vector<float> vec_acc;
      track.accelerations.push_back(vec_acc);
      for (std::size_t k=0; k!=size_accele; ++k) {
        in >> acc;
        track.accelerations[j].push_back(acc);
      }
    }

    std::size_t size_type;
    int track_unit_type;
    in >> size_type;
    OperaOption::Line line;
    OperaOption::Circle circle;
    for (std::size_t j=0; j!=size_type; ++j) {
      in >> track_unit_type;
      if (0 == track_unit_type) {
        in >> line.id
            >> line.start_x
            >> line.start_y
            >> line.end_x
            >> line.end_y;
        track.lines.push_back(line);
        track.types.push_back(OperaOption::LINE);
      } else if (1==track_unit_type) {
        in >> circle.id
            >> circle.start_x
            >> circle.start_y
            >> circle.center_x
            >> circle.center_y
            >> circle.angle;
        track.circles.push_back(circle);
        track.types.push_back(OperaOption::CIRCLE);
      }
    }
    
    std::size_t size_track_types;
    in >> size_track_types;
    int track_type = 0;
    for (std::size_t j=0; j!=size_track_types; ++j) {
      in >> track_type;
      track.track_types.push_back(track_type);
    }
    op.push_back_track(track);
  }
  return in;
}

bool OperaOption::operator==(const OperaOption& opera_option) const{
  bool flag = false;
  if (radars_.size() != opera_option.radars_.size()) {
    return false;
  } else {
    for (std::size_t i=0; i!=radars_.size(); ++i) {
      if (!(radars_[i].id == opera_option.radars_[i].id &&
          DoubleEqual(radars_[i].start_x, opera_option.radars_[i].start_x) &&
          DoubleEqual(radars_[i].start_y, opera_option.radars_[i].start_y) &&
          DoubleEqual(radars_[i].radius_x, opera_option.radars_[i].radius_x) &&
          DoubleEqual(radars_[i].radius_y, opera_option.radars_[i].radius_y) &&
          DoubleEqual(radars_[i].error.error_random_azimuth,
                      opera_option.radars_[i].error.error_random_azimuth) &&
          DoubleEqual(radars_[i].error.error_random_distance,
                      opera_option.radars_[i].error.error_random_distance) &&
          DoubleEqual(radars_[i].error.error_random_elevation,
                      opera_option.radars_[i].error.error_random_elevation) &&
          DoubleEqual(radars_[i].error.error_system_azimuth,
                      opera_option.radars_[i].error.error_system_azimuth) &&
          DoubleEqual(radars_[i].error.error_system_distance,
                      opera_option.radars_[i].error.error_system_distance) &&
          DoubleEqual(radars_[i].error.error_system_elevation,
                      opera_option.radars_[i].error.error_system_elevation)))
        return false;

      if (radars_[i].azimuth_range.size() 
          != opera_option.radars_[i].azimuth_range.size())
      return false;
      for (std::size_t j=0; j!=radars_[i].azimuth_range.size(); ++j) {
        if(!(DoubleEqual(radars_[i].azimuth_range[j].first,
            opera_option.radars_[i].azimuth_range[j].first) &&
            DoubleEqual(radars_[i].azimuth_range[j].second,
            opera_option.radars_[i].azimuth_range[j].second))) {
          return false;
        }
      }
    }
  }

  if (tracks_.size() != opera_option.tracks_.size()) {
    return false;
  } else {
    for (std::size_t i=0; i!=tracks_.size(); ++i) {
      if (!(tracks_[i].id == opera_option.tracks_[i].id &&
            tracks_[i].start_speeds.size()
                == opera_option.tracks_[i].start_speeds.size() &&
            tracks_[i].accelerations.size()
                == opera_option.tracks_[i].accelerations.size() &&
            tracks_[i].time_delays.size()
                == opera_option.tracks_[i].time_delays.size() &&
            tracks_[i].ids.size()
                == opera_option.tracks_[i].ids.size() &&
            tracks_[i].lines.size()
                == opera_option.tracks_[i].lines.size() &&
            tracks_[i].circles.size()
                == opera_option.tracks_[i].circles.size() &&
            tracks_[i].types.size()
                == opera_option.tracks_[i].types.size())) {
        return false;
      } else {
        return true;
      }
    }
  }
  return flag;
}

bool OperaOption::IsIDUnique() const {
  std::set<long long> ids; 
  for (std::size_t i=0; i!=radars_.size(); ++i) {
    if (ids.count(radars_[i].id) == 1)   
      return false;
    else
      ids.insert(radars_[i].id);
  }
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    if (ids.count(tracks_[i].id) == 1)
      return false;
    else
      ids.insert(tracks_[i].id);
    for (std::size_t j=0; j!=tracks_[i].ids.size(); ++j) {
      if (ids.count(tracks_[i].ids[j]) == 1)
        return false;
      else
        ids.insert(tracks_[i].ids[j]);
    }
  }
  return true;
}

bool OperaOption::IsIDExistInTrackSet(long long id) const {
  std::set<long long> ids;
  for (std::size_t i=0; i!=tracks_.size(); ++i) {
    for (std::size_t j=0; j!=tracks_[i].ids.size(); ++j) {
      ids.insert(tracks_[i].ids[j]);
    }
  }
  if (ids.count(id) == 1)
    return true;
  else 
    return false;
}

void OperaOption::Radar::set_type(RadarType radar_type) {
  type &= (~0x0ff);
  type += radar_type;
}

OperaOption::RadarType OperaOption::Radar::get_type() const {
  int result = type & 0x0ff;
  if (0 == result)
    return R_STATIC;
  else
    return R_DYNAMIC;
}

void OperaOption::Radar::set_type_trival(unsigned char type) {
  int val = ~(0x0ff << 8);
  this->type &= val;
  val = type;
  val = val << 0x08;
  this->type |= val;
}

unsigned char OperaOption::Radar::get_type_trival() const {
  int val = type;
  val = (val >> 8) & 0x0ff;
  return val;
}

std::vector<int> OperaOption::get_track_types() const {
    std::set<int> types;   
    for (size_t i=0; i!=tracks_.size(); ++i)
      types.insert(tracks_[i].reserve.type);
    std::vector<int> result(types.size());
    std::copy(types.begin(), types.end(), result.begin());
    return result;
}

std::vector<OperaOption::Track> OperaOption::get_tracks_by_type(int type) const {
    std::vector<Track> tracks;
    for (size_t i=0; i!=tracks_.size(); ++i) {
      if (type == tracks_[i].reserve.type)
        tracks.push_back(tracks_[i]);
    }
    return tracks;
}

} //namespace tools
