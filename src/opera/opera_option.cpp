#include "opera/opera_option.h"

#include <assert.h>

#include <sstream>

#include "map/map_projection.h"
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
  LogInfo("char: %d\n", radar.type);
  if (!ValidOfLongitude(radar.start_x)) {
    LogInfo("%f\n", radar.start_x);
  }
  assert(ValidOfLongitude(radar.start_x));
  assert(ValidOfLatitude(radar.start_y));
  assert(ValidOfLongitude(radar.radius_x));
  assert(ValidOfLatitude(radar.radius_y));
  assert(ValidOfCircleAngle(radar.angle_azimuth));
  assert(ValidOfCircleAngle(radar.angle_sector_range));
  assert(radar.error_system >= -10.0 && radar.error_system <= 10.0);
  assert(radar.error_random >= -10.0 && radar.error_random <= 10.0);
  assert(radar.error_overall >= -10.0 && radar.error_overall <= 10.0);
  radar.level_noise = 0.3 * radar.error_system + 0.3 * radar.error_random
    + 0.4 * radar.error_overall;
  assert(radar.level_noise >= 0.0 && radar.level_noise <= 256.0);
  radars_.push_back(radar);
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

void OperaOption::pop_object(long long id) {
  std::vector<Object>::iterator iter = objects_.begin();
  for (; iter != objects_.end(); ++iter) {
    if (iter->id == id) {
      objects_.erase(iter);
      return;
    }
  }
}

void OperaOption::push_back_track(Track& track) {
  assert(track.lines.size() + track.circles.size()
      + track.eclipses.size() == track.types.size());
  assert(track.ids.size() == static_cast<std::size_t>(track.batch_count));
  assert(track.level_noise_track >= 0.0 && track.level_noise_track <= 256);
  assert(track.id >= 0);
  for (std::size_t i = 0; i != track.start_speeds.size(); ++i)
    assert(track.start_speeds[i] >= 0.0 && track.start_speeds[i] <= 10);
  tracks_.push_back(track); 
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
      FromWgsToPixel(&tracks_[i].circles[j].side_x,
                     &tracks_[i].circles[j].side_y);
      FromWgsToPixel(&tracks_[i].circles[j].angle_x,
                     &tracks_[i].circles[j].angle_y);
    }
    for (std::size_t j=0; j!=tracks_[i].eclipses.size(); ++j) {
      FromWgsToPixel(&tracks_[i].eclipses[j].start_x,
                     &tracks_[i].eclipses[j].start_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].center_x,
                     &tracks_[i].eclipses[j].center_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].side_x,
                     &tracks_[i].eclipses[j].side_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].end_x,
                     &tracks_[i].eclipses[j].end_y);
      FromWgsToPixel(&tracks_[i].eclipses[j].angle_x,
                     &tracks_[i].eclipses[j].angle_y);
    }
  }
}

void OperaOption::ConvertToPlaneCoodinate(void (Conv)(double*, double*)) {
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
      Conv(&tracks_[i].circles[j].side_x,
                     &tracks_[i].circles[j].side_y);
      Conv(&tracks_[i].circles[j].angle_x,
                     &tracks_[i].circles[j].angle_y);
    }
    for (std::size_t j=0; j!=tracks_[i].eclipses.size(); ++j) {
      Conv(&tracks_[i].eclipses[j].start_x,
                     &tracks_[i].eclipses[j].start_y);
      Conv(&tracks_[i].eclipses[j].center_x,
                     &tracks_[i].eclipses[j].center_y);
      Conv(&tracks_[i].eclipses[j].side_x,
                     &tracks_[i].eclipses[j].side_y);
      Conv(&tracks_[i].eclipses[j].end_x,
                     &tracks_[i].eclipses[j].end_y);
      Conv(&tracks_[i].eclipses[j].angle_x,
                     &tracks_[i].eclipses[j].angle_y);
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
        tracks_[i].lines,
        tracks_[i].circles,
        tracks_[i].eclipses,
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
  double x_sift = GetRandNumber(seed + 1) * level_noise;
  double y_sift = GetRandNumber(seed + 2) * level_noise;
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
    track_internal.circles[i].side_x += x_sift;
    track_internal.circles[i].side_y += y_sift;
    track_internal.circles[i].angle_x += x_sift;
    track_internal.circles[i].angle_y += y_sift;
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
        << op.radars_[i].error_system << " "   
        << op.radars_[i].error_random << " "   
        << op.radars_[i].error_overall << " "   
        << op.radars_[i].angle_azimuth << " "   
        << op.radars_[i].angle_sector_range << std::endl;
  }
  os << op.tracks_.size() << " ";
  for (std::size_t i=0; i!=op.tracks_.size(); ++i) {
    os << op.tracks_[i].id << " ";
    os << op.tracks_[i].batch_count << " ";
    os << op.tracks_[i].level_noise_track << " ";
    os << op.tracks_[i].start_speeds.size() << " ";
    
    for (std::size_t j=0; j!=op.tracks_[i].start_speeds.size(); ++j) {
      os << op.tracks_[i].start_speeds[j] << " "
         << op.tracks_[i].accelerations[j] << " "
         << op.tracks_[i].time_delays[j] << " "
         << op.tracks_[i].ids[j] << " ";
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
            << op.tracks_[i].circles[circle_index].side_x << " "
            << op.tracks_[i].circles[circle_index].side_y << " "
            << op.tracks_[i].circles[circle_index].angle_x << " "
            << op.tracks_[i].circles[circle_index].angle_y << " ";
      }
    }
  }
  return os;
}
    
std::istream& operator>> (std::istream& in, OperaOption& op) {
  op.radars_.clear();
  op.objects_.clear();
  op.tracks_.clear();
  std::size_t size_radar;
  in >> size_radar;
  OperaOption::Radar radar;
  for (std::size_t i=0; i!=size_radar; ++i) {
    in >> radar.id
        >> radar.type
        >> radar.start_x
        >> radar.start_y
        >> radar.radius_x
        >> radar.radius_y
        >> radar.error_system
        >> radar.error_random
        >> radar.error_overall
        >> radar.angle_azimuth
        >> radar.angle_sector_range;
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
    
    in >> track.id;
    in >> track.batch_count;
    in >> track.level_noise_track;

    std::size_t size_ids;
    in >> size_ids;

    double temp;
    for (std::size_t j=0; j!=size_ids; ++j) {
      in >> temp;
      track.start_speeds.push_back(temp);
      in >> temp;
      track.accelerations.push_back(temp);
      in >> temp;
      track.time_delays.push_back(temp);
      in >> temp;
      track.ids.push_back(static_cast<long long>(temp));
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
            >> circle.side_x
            >> circle.side_y
            >> circle.angle_x
            >> circle.angle_y;
        track.circles.push_back(circle);
        track.types.push_back(OperaOption::CIRCLE);
      }
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
          DoubleEqual(radars_[i].error_system,
                      opera_option.radars_[i].error_system) &&
          DoubleEqual(radars_[i].error_random,
                      opera_option.radars_[i].error_random) &&
          DoubleEqual(radars_[i].error_overall,
                      opera_option.radars_[i].error_overall) &&
          DoubleEqual(radars_[i].angle_azimuth,
                      opera_option.radars_[i].angle_azimuth) &&
          DoubleEqual(radars_[i].angle_sector_range,
                      opera_option.radars_[i].angle_sector_range))) {
        return false;
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

} //namespace tools
