#include "opera/radar.h"
#include "util/tool.h"

#include <iomanip>

namespace {

bool EqualOfVectorOfDouble(const std::vector<double>& lhs,
                           const std::vector<double>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (std::size_t i=0; i!=lhs.size(); ++i)
    if (!tools::DoubleEqual(lhs[i], rhs[i]))
      return false;
  return true;
}

bool EqualOfVectorOfLong(const std::vector<long long>& lhs,
                           const std::vector<long long>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (std::size_t i=0; i!=lhs.size(); ++i)
    if (lhs[i] != rhs[i])
      return false;
  return true;
}

bool EqualOfVectorOfPoint2D(const std::vector<tools::Point2D>& lhs,
                           const std::vector<tools::Point2D>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (std::size_t i=0; i!=lhs.size(); ++i)
    if (lhs[i].x != rhs[i].x || lhs[i].y != rhs[i].y)
      return false;
  return true;
}

bool EqualOfVectorOfRadarError(const std::vector<tools::Radar2D::RadarError>& lhs,
                           const std::vector<tools::Radar2D::RadarError>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (std::size_t i=0; i!=lhs.size(); ++i)
    if (lhs != rhs)
      return false;
  return true;
}

} //namespace

namespace tools{

  bool Radar2D::RadarError::operator==(
      const RadarError& radar_error) const{
    if (DoubleEqual(this->error_random_distance, 
          radar_error.error_random_distance) &&
        DoubleEqual(this->error_random_azimuth,
          radar_error.error_random_azimuth) &&
        DoubleEqual(this->error_random_elevation,
          radar_error.error_random_elevation) &&
        DoubleEqual(this->error_system_distance, 
          radar_error.error_system_distance) &&
        DoubleEqual(this->error_system_azimuth,
          radar_error.error_system_azimuth) &&
        DoubleEqual(this->error_system_elevation,
          radar_error.error_system_elevation) &&
        DoubleEqual(this->error_overall_distance, 
          radar_error.error_overall_distance) &&
        DoubleEqual(this->error_overall_azimuth,
          radar_error.error_overall_azimuth) &&
        DoubleEqual(this->error_overall_elevation,
          radar_error.error_overall_elevation) &&
        DoubleEqual(this->error_distance, 
          radar_error.error_distance) &&
        DoubleEqual(this->error_velocity,
          radar_error.error_velocity) &&
        DoubleEqual(this->error_direction,
            radar_error.error_direction)) {
      return true;
    }
    return false;   
  }

std::ostream& operator<<(std::ostream& out,
    const Radar2D::RadarError& radar_error) {
  out << std::fixed << std::setprecision(20);
  out << radar_error.error_random_distance << " ";
  out << radar_error.error_random_azimuth << " ";
  out << radar_error.error_random_elevation << " ";

  out << radar_error.error_system_distance << " ";
  out << radar_error.error_system_azimuth << " ";
  out << radar_error.error_system_elevation << " ";

  out << radar_error.error_overall_distance << " ";
  out << radar_error.error_overall_azimuth << " ";
  out << radar_error.error_overall_elevation << " ";

  out << radar_error.error_distance << " ";
  out << radar_error.error_velocity << " ";
  out << radar_error.error_direction << " ";
  return out;
}

std::istream& operator>>(std::istream& in, Radar2D::RadarError& radar_error) {
  in >> radar_error.error_random_distance;
  in >> radar_error.error_random_azimuth;
  in >> radar_error.error_random_elevation;

  in >> radar_error.error_system_distance;
  in >> radar_error.error_system_azimuth;
  in >> radar_error.error_system_elevation;

  in >> radar_error.error_overall_distance;
  in >> radar_error.error_overall_azimuth;
  in >> radar_error.error_overall_elevation;

  in >> radar_error.error_distance;
  in >> radar_error.error_velocity;
  in >> radar_error.error_direction;
  return in;
}

bool Radar2D::RadarState::operator==(const RadarState& lhs) const {
  if (this->id == lhs.id &&
      this->point.x == lhs.point.x &&
      this->point.y == lhs.point.y &&
      EqualOfVectorOfLong(this->ids, lhs.ids) &&
      EqualOfVectorOfPoint2D(this->targets, lhs.targets) &&
      EqualOfVectorOfDouble(this->targets_angle_azimuth,
          lhs.targets_angle_azimuth) &&
      EqualOfVectorOfDouble(this->targets_real_distance,
          lhs.targets_real_distance) &&
      EqualOfVectorOfDouble(this->targets_real_elevation,
          lhs.targets_real_elevation) &&
      EqualOfVectorOfDouble(this->targets_real_velocity,
          lhs.targets_real_velocity) &&
      EqualOfVectorOfPoint2D(this->targets_radar, lhs.targets_radar) &&
      EqualOfVectorOfDouble(this->targets_detected_distance,
          lhs.targets_detected_distance) &&
      EqualOfVectorOfDouble(this->targets_detected_elevation,
          lhs.targets_detected_elevation) &&
      EqualOfVectorOfDouble(this->targets_detected_velocity,
          lhs.targets_detected_velocity) &&
      EqualOfVectorOfPoint2D(this->targets_filter, lhs.targets_filter) &&
      EqualOfVectorOfRadarError(this->targets_error, lhs.targets_error)) {
    return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& out, 
    const Radar2D::RadarState& radar_state) {
  out << std::fixed << std::setprecision(20);
  out << radar_state.id << " ";
  out << radar_state.type<< " ";
  out << radar_state.point.x << " ";
  out << radar_state.point.y << " ";

  out << radar_state.ids.size() << " ";
  for (std::size_t i=0; i!=radar_state.ids.size(); ++i)
    out << radar_state.ids[i] << " ";

  out << radar_state.targets.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets.size(); ++i) {
    out << radar_state.targets[i].x << " ";
    out << radar_state.targets[i].y << " ";
  }

  out << radar_state.targets_angle_azimuth.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_angle_azimuth.size(); ++i)
    out << radar_state.targets_angle_azimuth[i] << " ";

  out << radar_state.targets_real_distance.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_real_distance.size(); ++i)
    out << radar_state.targets_real_distance[i] << " ";

  out << radar_state.targets_real_elevation.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_real_elevation.size(); ++i)
    out << radar_state.targets_real_elevation[i] << " ";

  out << radar_state.targets_real_velocity.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_real_velocity.size(); ++i)
    out << radar_state.targets_real_velocity[i] << " ";

  out << radar_state.targets_radar.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_radar.size(); ++i) {
    out << radar_state.targets_radar[i].x << " ";
    out << radar_state.targets_radar[i].y << " ";
  }

  out << radar_state.targets_angle_azimuth.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_angle_azimuth.size(); ++i)
    out << radar_state.targets_angle_azimuth[i] << " ";

  out << radar_state.targets_detected_distance.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_detected_distance.size(); ++i)
    out << radar_state.targets_detected_distance[i] << " ";

  out << radar_state.targets_detected_elevation.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_detected_elevation.size(); ++i)
    out << radar_state.targets_detected_elevation[i] << " ";

  out << radar_state.targets_detected_velocity.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_detected_velocity.size(); ++i)
    out << radar_state.targets_detected_velocity[i] << " ";

  out << radar_state.targets_filter.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_filter.size(); ++i) {
    out << radar_state.targets_filter[i].x << " ";
    out << radar_state.targets_filter[i].y << " ";
  }
  
  out << radar_state.targets_error.size() << " ";
  for (std::size_t i=0; i!=radar_state.targets_error.size(); ++i)
    out << radar_state.targets_error[i] << " ";
  return out;
}
                                    
std::istream& operator>>(std::istream& in, Radar2D::RadarState& radar_state) {
  radar_state.ids.clear();
  radar_state.targets.clear();
  radar_state.targets_angle_azimuth.clear();
  radar_state.targets_real_distance.clear();
  radar_state.targets_real_elevation.clear();
  radar_state.targets_real_velocity.clear();
  radar_state.targets_radar.clear();
  radar_state.targets_detected_azimuth.clear();
  radar_state.targets_detected_distance.clear();
  radar_state.targets_detected_elevation.clear();
  radar_state.targets_detected_velocity.clear();
  radar_state.targets_filter.clear();
  radar_state.targets_error.clear();

  in >> radar_state.id;
  in >> radar_state.type;
  in >> radar_state.point.x;
  in >> radar_state.point.y;

  std::size_t length;

  long long id;
  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> id;
    radar_state.ids.push_back(id);
  }

  Point2D point;
  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> point.x >> point.y;
    radar_state.targets.push_back(point);
  }

  double temp_double;
  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_angle_azimuth.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_real_distance.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_real_elevation.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_real_velocity.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> point.x >> point.y;
    radar_state.targets_radar.push_back(point);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_detected_azimuth.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_detected_distance.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_detected_elevation.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> temp_double;
    radar_state.targets_detected_velocity.push_back(temp_double);
  }

  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> point.x >> point.y;
    radar_state.targets_filter.push_back(point);
  }

  Radar2D::RadarError radar_error;
  in >> length;
  for (std::size_t i=0; i!=length; ++i) {
    in >> radar_error;
    radar_state.targets_error.push_back(radar_error);
  }

  return in;
}

} //namespace tools