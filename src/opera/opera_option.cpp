#include "opera/opera_option.h"

#include <assert.h>

#include <algorithm>
#include <set>
#include <sstream>
#include <iomanip>

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
  assert(radar.get_type() == R_STATIC || radar.get_type() == R_DYNAMIC);
  assert(ValidOfLongitude(radar.start_x));
  assert(ValidOfLatitude(radar.start_y));
  assert(ValidOfLongitude(radar.radius_x));
  assert(ValidOfLatitude(radar.radius_y));
  for (std::size_t i=0; i!=radar.azimuth_range.size(); ++i) {
    assert(ValidOfCircleAngle(radar.azimuth_range[i].first));
    assert(ValidOfCircleAngle(radar.azimuth_range[i].second));
  }

  if (radar.get_type() == R_STATIC) {
    radar.track_id = 0;
  } 
  if (radar.get_type() == R_DYNAMIC){
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

template <class T>
void transform_to_ostream(std::ostream& out, const std::vector<T>& vec) {
  out << std::fixed << std::setprecision(20);
  out << vec.size() << " ";
  for (std::size_t i=0; i!=vec.size(); ++i)
    out << vec[i] << " ";
}

void transform_to_ostream(std::ostream& out,
    const std::vector<OperaOption::TrackUnitType>& vec) {
  out << std::fixed << std::setprecision(20);
  out << vec.size() << " ";
  for (std::size_t i=0; i!=vec.size(); ++i)
    if (vec[i] == OperaOption::LINE)
      out << 0 << " ";
    else if (vec[i] == OperaOption::CIRCLE)
      out << 1 << " ";
}

template <class T>
void transform_from_istream(std::istream& in, std::vector<T>& vec) {
  vec.clear();
  std::size_t length;
  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    T temp;
    in >> temp; 
    vec.push_back(temp);
  }
}

void transform_from_istream(std::istream& in,
    std::vector<OperaOption::TrackUnitType>& vec) {
  vec.clear();
  std::size_t length;
  in >> length;
  int temp;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp; 
    if (0 == temp)
      vec.push_back(OperaOption::LINE);
    else if (1 == temp)
      vec.push_back(OperaOption::CIRCLE);
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
        tracks_[i].height,
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

std::ostream& operator<< (std::ostream& out, const OperaOption& op) {
  out << std::fixed << std::setprecision(20);
  out << op.interval_ << " ";
  transform_to_ostream(out, op.radars_);
  transform_to_ostream(out, op.tracks_);
  return out;
}
    
std::istream& operator>> (std::istream& in, OperaOption& op) {
  in >> op.interval_;
  transform_from_istream(in, op.radars_);
  transform_from_istream(in, op.tracks_);
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

bool OperaOption::Reserve::operator==(const Reserve& reserve) const {
  if (this->data.size() != reserve.data.size())
    return false;
  for (std::size_t i=0; i!=reserve.data.size(); ++i)
    if (!DoubleEqual(this->data[i], reserve.data[i]))
      return false;
  return true;
}

bool OperaOption::Reserve::operator!=(const Reserve& reserve) const {
  return !(reserve == (*this));
}

std::istream& operator>>(std::istream& in, OperaOption::Reserve& reserve) {
  reserve.data.clear();
  std::size_t length;
  double temp;

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp;
    reserve.data.push_back(temp); 
  }
  return in;
}

std::ostream& operator<< (std::ostream& out, const OperaOption::Reserve& reserve) {
  out << std::fixed << std::setprecision(20);
  out << reserve.data.size() << " ";
  for (std::size_t i=0; i!=reserve.data.size(); ++i)
    out << reserve.data[i] << " ";
  return out;
}

bool OperaOption::Error::operator==(const Error& error) const {
  if (DoubleEqual(this->error_random_azimuth, error.error_random_azimuth) &&
      DoubleEqual(this->error_random_distance, error.error_random_distance) &&
      DoubleEqual(this->error_random_elevation, error.error_random_elevation) &&
      DoubleEqual(this->error_system_azimuth, error.error_system_azimuth) &&
      DoubleEqual(this->error_system_distance, error.error_system_distance) &&
      DoubleEqual(this->error_system_elevation, error.error_system_elevation))
    return true;
  return false;
}

bool OperaOption::Error::operator!=(const Error& error) const {
  return !(error == (*this));
}

std::istream& operator>> (std::istream& in, OperaOption::Error& error) {
  in >> error.error_random_distance;
  in >> error.error_random_azimuth;
  in >> error.error_random_elevation;
  in >> error.error_system_distance;
  in >> error.error_system_azimuth;
  in >> error.error_system_elevation;
  return in;
}

std::ostream& operator<< (std::ostream& out, const OperaOption::Error& error) {
  out << std::fixed << std::setprecision(20);
  out << error.error_random_distance << " ";
  out << error.error_random_azimuth<< " ";
  out << error.error_random_elevation<< " ";
  out << error.error_system_distance << " ";
  out << error.error_system_azimuth << " ";
  out << error.error_system_elevation << " ";
  return out;
}


bool OperaOption::Radar::operator==(const OperaOption::Radar& radar) const {
  if (this->id != radar.id ||
      this->type != radar.type ||
      this->detecting_objects_types != radar.detecting_objects_types ||
      this->track_id != radar.track_id ||
      !DoubleEqual(this->start_x, radar.start_x) ||
      !DoubleEqual(this->start_y, radar.start_y) ||
      !DoubleEqual(this->radius_x, radar.radius_x) ||
      !DoubleEqual(this->radius_y, radar.radius_y) ||
      !DoubleEqual(this->height, radar.height) ||
      this->error != radar.error ||
      this->azimuth_range.size() != radar.azimuth_range.size() ||
      this->data != radar.data
      )
    return false;
  std::size_t length = radar.azimuth_range.size();
  for (std::size_t i=0; i!=length; ++i) {
    if (!DoubleEqual(this->azimuth_range[i].first,
          radar.azimuth_range[i].first) ||
        !DoubleEqual(this->azimuth_range[i].second,
          radar.azimuth_range[i].second))
      return false;
  }
  return true;
}

bool OperaOption::Radar::operator!=(const OperaOption::Radar& radar) const {
  return !(radar == (*this));
}

std::ostream& operator<< (std::ostream& out, const OperaOption::Radar& radar) {
  out << std::fixed << std::setprecision(20);
  out << radar.id << " ";
  out << radar.type << " ";
  out << radar.detecting_objects_types << " ";
  out << radar.track_id << " ";
  out << radar.start_x << " ";
  out << radar.start_y << " ";
  out << radar.radius_x << " ";
  out << radar.radius_y << " ";
  out << radar.height << " ";
  out << radar.error << " ";
  out << radar.azimuth_range.size() << " ";
  for (std::size_t i=0; i!=radar.azimuth_range.size(); ++i)
    out << radar.azimuth_range[i].first << " "
        << radar.azimuth_range[i].second << " ";
  out << radar.data << " ";
  return out;
}

std::istream& operator>> (std::istream& in, OperaOption::Radar& radar) {
  radar.azimuth_range.clear();

  in >> radar.id;
  in >> radar.type;
  in >> radar.detecting_objects_types;
  in >> radar.track_id;
  in >> radar.start_x;
  in >> radar.start_y;
  in >> radar.radius_x;
  in >> radar.radius_y;
  in >> radar.height;
  in >> radar.error;

  std::size_t length;
  std::pair<double, double> pair_double;
  std::pair<int, int> pair_int;

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> pair_double.first >> pair_double.second;
    radar.azimuth_range.push_back(pair_double);
  }
  in >> radar.data;
  return in;
}

bool OperaOption::Line::operator==(const Line& line) const {
  if (this->id == line.id &&
      DoubleEqual(this->start_x, line.start_x) &&
      DoubleEqual(this->start_y, line.start_y) &&
      DoubleEqual(this->end_x, line.end_x) &&
      DoubleEqual(this->end_y, line.end_y))
    return true;
  return false;
}

bool OperaOption::Line::operator!=(const Line& line) const {
  return !((*this) == line);
}

std::istream& operator>> (std::istream& in, OperaOption::Line& line) {
  in >> line.id;
  in >> line.start_x;
  in >> line.start_y;
  in >> line.end_x;
  in >> line.end_y;
  return in;
}

std::ostream& operator<< (std::ostream& out, const OperaOption::Line& line) {
  out << std::fixed << std::setprecision(20);
  out << line.id << " ";
  out << line.start_x << " ";
  out << line.start_y << " ";
  out << line.end_x << " ";
  out << line.end_y << " ";
  return out;
}

bool OperaOption::Circle::operator==(const Circle& circle) const {
  if (this->id == circle.id &&
      DoubleEqual(this->start_x, circle.start_x) &&
      DoubleEqual(this->start_y, circle.start_y) &&
      DoubleEqual(this->center_x, circle.center_x) &&
      DoubleEqual(this->center_y, circle.center_y) &&
      DoubleEqual(this->angle, circle.angle))
    return true;
  return false;
}

bool OperaOption::Circle::operator!=(const Circle& circle) const {
  return !((*this) == circle);
}

std::istream& operator>> (std::istream& in, OperaOption::Circle& circle) {
  in >> circle.id;
  in >> circle.start_x;
  in >> circle.start_y;
  in >> circle.center_x;
  in >> circle.center_y;
  in >> circle.angle;
  return in;
}

std::ostream& operator<< (std::ostream& out, const OperaOption::Circle& circle) {
  out << std::fixed << std::setprecision(20);
  out << circle.id << " ";
  out << circle.start_x << " ";
  out << circle.start_y << " ";
  out << circle.center_x << " ";
  out << circle.center_y << " ";
  out << circle.angle << " ";
  return out;
}

bool OperaOption::Track::operator==(const Track& track) const {
  if (this->id != track.id ||
      !DoubleEqual(this->height, track.height) ||
      this->data != track.data ||
      this->reserve.type != track.reserve.type ||
      this->start_speeds.size() != track.start_speeds.size() ||
      this->accelerations.size() != track.accelerations.size() ||
      this->time_delays.size() != track.time_delays.size() ||
      this->batch_count != track.batch_count ||
      !DoubleEqual(this->level_noise_track, track.level_noise_track) ||
      this->ids.size() != track.ids.size() ||
      this->lines.size() != track.lines.size() ||
      this->circles.size() != track.circles.size() ||
      this->types.size() != track.types.size() ||
      this->track_types.size() != track.track_types.size() )
    return false;

  for (std::size_t i=0; i!=this->start_speeds.size(); ++i)
    if (!DoubleEqual(this->start_speeds[i], track.start_speeds[i]))
      return false;

  for (std::size_t i=0; i!=this->accelerations.size(); ++i) {
    if (this->accelerations[i].size() != track.accelerations[i].size())
      return false;
    for (std::size_t j=0; j!=this->accelerations[i].size(); ++j)
      if (!DoubleEqual(static_cast<double>(this->accelerations[i][j]),
            static_cast<double>(track.accelerations[i][j])))
        return false;
  }

  for (std::size_t i=0; i!=this->time_delays.size(); ++i)
    if (!DoubleEqual(this->time_delays[i], track.time_delays[i]))
      return false;

  for (std::size_t i=0; i!=this->ids.size(); ++i)
    if (this->ids[i] != track.ids[i])
      return false;

  for (std::size_t i=0; i!=this->lines.size(); ++i)
    if (this->lines[i] != track.lines[i])
      return false;

  for (std::size_t i=0; i!=this->circles.size(); ++i)
    if (this->circles[i] != track.circles[i])
      return false;

  for (std::size_t i=0; i!=this->types.size(); ++i)
    if (this->types[i] != track.types[i])
      return false;

  for (std::size_t i=0; i!=this->track_types.size(); ++i)
    if (this->track_types[i] != track.track_types[i])
      return false;

  return true;
}

bool OperaOption::Track::operator!=(const Track& track) const {
  return !((*this) == track);
}

int OperaOption::Reserve::get_int(int id) const {
  return static_cast<int>(get_double(id));
}

void OperaOption::Reserve::set_int(int id, int val) {
  set_double(id, static_cast<double>(val));
}

double OperaOption::Reserve::get_double(int id) const {
  std::size_t i = 0;
  while (i < data.size()) {
    if (static_cast<int>(data[i]) == id && static_cast<int>(data[i+1]) == kDouble) {
      return data[i+2];
    } else if ( static_cast<int>(data[i+1]) == kDouble ) {
      i += 3;
    } else if ( static_cast<int>(data[i+1]) == kString ) {
      i += (3+static_cast<int>(data[i+2]));
    }
  }
  return 0.0;
}

void OperaOption::Reserve::set_double(int id, double val) {
  std::size_t i = 0;
  while (i < data.size()) {
    if (static_cast<int>(data[i]) == id && static_cast<int>(data[i+1]) == kDouble) {
      data[i+2] = val;
      return;
    } else if ( static_cast<int>(data[i+1]) == kDouble ) {
      i += 3;
    } else if ( static_cast<int>(data[i+1]) == kString ) {
      i += (3+static_cast<int>(data[i+2]));
    }
  }
  data.push_back(static_cast<double>(id));   
  data.push_back(static_cast<double>(kDouble));   
  data.push_back(val);
}

std::string OperaOption::Reserve::get_string(int id) const {
  std::size_t i = 0;
  while (i < data.size()) {
    if (static_cast<int>(data[i]) == id && static_cast<int>(data[i+1]) == kString) {
      int len = static_cast<int>(data[i+2]);
      char* tmp = new char[len+1];
      for (int j=0; j!=len; ++j)
        tmp[j] = static_cast<char>(data[i+3+j]);
      tmp[len] = 0;
      std::string str = tmp;
      delete tmp;
      return str;
    } else if ( static_cast<int>(data[i+1]) == kDouble ) {
      i += 3;
    } else if ( static_cast<int>(data[i+1]) == kString ) {
      i += (3+static_cast<int>(data[i+2]));
    }
  }
  return "";
}

void OperaOption::Reserve::set_string(int id, const std::string& val) {
  std::size_t i = 0;
  while (i < data.size()) {
    if (static_cast<int>(data[i]) == id && static_cast<int>(data[i+1]) == kString) {
      int len = static_cast<int>(data[i+2]);
      std::vector<double>::iterator iter = data.begin();
      iter += i; 
      data.erase(iter, iter+len+3);
      break;
    } else if ( static_cast<int>(data[i+1]) == kDouble ) {
      i += 3;
    } else if ( static_cast<int>(data[i+1]) == kString ) {
      i += (3+static_cast<int>(data[i+2]));
    }
  }
  data.push_back(static_cast<double>(id));   
  data.push_back(static_cast<double>(kString));   
  data.push_back(static_cast<double>(val.length()));
  for (std::size_t i=0; i!=val.length(); ++i)
    data.push_back(static_cast<double>(val[i]));
}

std::istream& operator>> (std::istream& in, OperaOption::Track& track) {
  in >> track.id;
  in >> track.height;
  in >> track.data;
  in >> track.reserve.type;
  transform_from_istream(in, track.start_speeds);

  std::size_t length;
  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    std::vector<double> temp;
    transform_from_istream(in, temp);
    track.accelerations.push_back(temp);
  }

  transform_from_istream(in, track.time_delays);
  
  in >> track.batch_count;
  in >> track.level_noise_track;

  transform_from_istream(in, track.ids);
  transform_from_istream(in, track.lines);
  transform_from_istream(in, track.circles);
  transform_from_istream(in, track.types);
  transform_from_istream(in, track.track_types);

  return in;
}

std::ostream& operator<< (std::ostream& out, const OperaOption::Track& track) {
  out << std::fixed << std::setprecision(20);
  out << track.id << " ";
  out << track.height << " ";
  out << track.data << " ";
  out << track.reserve.type << " ";

  transform_to_ostream(out, track.start_speeds);

  out << track.accelerations.size() << " ";
  for (std::size_t i=0; i!=track.accelerations.size(); ++i) {
    transform_to_ostream(out, track.accelerations[i]);
  }

  transform_to_ostream(out, track.time_delays);
  
  out << track.batch_count << " ";
  out << track.level_noise_track << " ";

  transform_to_ostream(out, track.ids);
  transform_to_ostream(out, track.lines);
  transform_to_ostream(out, track.circles);
  transform_to_ostream(out, track.types);
  transform_to_ostream(out, track.track_types);

  return out;
}

} //namespace tools
