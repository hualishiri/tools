#include "opera/radar_sector.h"

#include <map>

#include "util/logger.h"
#include "util/tool.h"

namespace {

double GetRandError(int seed, double data) {
  return data * 3.0 * tools::GetRandNumber(seed);
}

}

namespace tools {

SectorRadar::SectorRadar(Radar* radar, RadarNoise* radar_noise)
  : radar_(radar), radar_noise_(radar_noise) {
  assert(radar_->id > 0);

  for (std::size_t i=0; i!=radar->azimuth_range.size(); ++i) {
    assert(radar_->azimuth_range[i].first >= 0.0 && 
        radar_->azimuth_range[i].first <= 2.0 * T_PI);
    assert(radar_->azimuth_range[i].second >= 0.0 &&
        radar_->azimuth_range[i].second <= 2.0 * T_PI);
  }

  assert(radar_->distance_detect >= 0.0);
  assert(radar_->error_random_distance > 0.0); 
  assert(radar_->error_random_azimuth >= 0.0 && 
      radar_->error_random_azimuth <= 2.0 * T_PI);
  assert(radar_->error_random_elevation >= 0.0 &&
      radar_->error_random_elevation <= (T_PI / 2.0));

  assert(radar_->distance_detect >= 0.0);
  assert(radar_->error_system_distance > 0.0); 
  assert(radar_->error_system_azimuth >= 0.0 && 
      radar_->error_system_azimuth <= 2.0 * T_PI);
  assert(radar_->error_system_elevation >= 0.0 &&
      radar_->error_system_elevation <= (T_PI / 2.0));
}

void SectorRadar::GetState(
    const TrackSet2D::TrackSetState& track_set_state,
    RadarState& radar_state) {
  radar_state.id = radar_->id;
  radar_state.type = radar_->type;
  radar_state.point.x = radar_->x;
  radar_state.point.y = radar_->y;
  radar_state.height = radar_->height;
  ClearRadarState(radar_state);

  std::size_t index_i = -1;
  for (std::vector<Track2D::TrackState>::const_iterator iter 
      = track_set_state.track_set_state.begin();
      iter != track_set_state.track_set_state.end();
      ++iter) {
    ++index_i;
    Target target = {iter->point.x, iter->point.y, iter->track_type};
    if (IsCaptured(*radar_, target)) {
      radar_state.ids.push_back(iter->id);
      radar_state.targets.push_back(iter->point);  
      radar_state.targets_height.push_back(iter->height);
      radar_state.targets_real_velocity.push_back(iter->speed);
    } 
  }
  CalculateRadarState(radar_state);
  radar_state_last_ = radar_state;
  CalculateObjectCourse(radar_state);

  assert(radar_state.ids.size() == radar_state.targets.size());
  assert(radar_state.ids.size() == radar_state.targets_angle_azimuth.size());
  assert(radar_state.ids.size() == radar_state.targets_real_distance.size());
  assert(radar_state.ids.size() == radar_state.targets_real_elevation.size());
  assert(radar_state.ids.size() == radar_state.targets_real_velocity.size());

  assert(radar_state.ids.size() == radar_state.targets_radar.size());
  assert(radar_state.ids.size() == radar_state.targets_detected_azimuth.size());
  assert(radar_state.ids.size() == radar_state.targets_detected_distance.size());
  assert(radar_state.ids.size() == radar_state.targets_detected_elevation.size());
  assert(radar_state.ids.size() == radar_state.targets_detected_velocity.size());

  assert(radar_state.ids.size() == radar_state.targets_filter.size());
  assert(radar_state.ids.size() == radar_state.targets_error.size());
}

bool SectorRadar::IsCaptured(const Radar& radar,
                                   const Target& target) const {
  double distance = Distance2D(radar.x, radar.y, target.x, target.y);
  if (distance >= radar_->distance_detect)
    return false;
  if (!(radar.detecting_objects_types & target.target_type))
    return false;
  double angle_target_amuzith = GetAngleOfAzimuth(Point2D(radar.x, radar.y),
                                                  Point2D(target.x, target.y));
  return IsInRange(radar_->azimuth_range, angle_target_amuzith);
}

float SectorRadar::GetAngleOfAzimuth(const Point2D& radar,
                                     const Point2D& target) const {
  return AngleFromStartByClockInCircle(radar.x,
                                       radar.y + 1.0,
                                       radar.x,
                                       radar.y,
                                       target.x,
                                       target.y);
}

void SectorRadar::SetPosition(double x, double y) {
  radar_->x = x;
  radar_->y = y;
}

bool SectorRadar::IsInRange(
    const std::vector<std::pair<double, double> > azimuth_range,
    double target_angle) const {
  for (std::size_t i=0; i!=azimuth_range.size(); ++i) {
    if (target_angle >= azimuth_range[i].first && 
        target_angle <= azimuth_range[i].first + azimuth_range[i].second)
      return true;
  }
  return false;
}

void SectorRadar::CalculateRadarError(int seed) {
  error_.error_random_distance = GetRandError(seed, radar_->error_random_distance);
  error_.error_random_azimuth = GetRandError(seed, radar_->error_random_azimuth);
  error_.error_random_elevation = GetRandError(seed, radar_->error_random_elevation);

  error_.error_system_distance = radar_->error_system_distance;
  error_.error_system_azimuth = radar_->error_system_azimuth;
  error_.error_system_elevation = radar_->error_system_elevation;

  error_.error_overall_distance = error_.error_random_distance
      + error_.error_system_distance;
  error_.error_overall_azimuth = error_.error_random_azimuth
      + error_.error_system_azimuth;
  error_.error_overall_elevation = error_.error_random_elevation
      + error_.error_system_elevation;
}

void SectorRadar::CalculateRadarState(RadarState& radar_state) {
  std::size_t size_target = radar_state.targets.size();
  for (std::size_t i=0; i!=size_target; ++i) {
    CalculateRadarError(i);
    radar_state.targets_error.push_back(error_);

    radar_state.targets_angle_azimuth.push_back(GetAngleOfAzimuth(
        Point2D(radar_state.point.x, radar_state.point.y), 
        Point2D(radar_state.targets[i].x, radar_state.targets[i].y)));

    radar_state.targets_real_distance.push_back(Distance2D(radar_state.point.x,
                                       radar_state.point.y,
                                       radar_state.targets[i].x,
                                       radar_state.targets[i].y));
    radar_state.targets_real_elevation.push_back(Elevation(
        radar_state.targets_real_distance[i],
        radar_state.targets_height[i]));

    radar_state.targets_detected_azimuth.push_back(
      radar_state.targets_angle_azimuth[i] + 
      radar_state.targets_error[i].error_overall_azimuth);
    if (radar_state.targets_detected_azimuth[i] > 2.0 * T_PI)
      radar_state.targets_detected_azimuth[i] -= 2.0 * T_PI;
    else if (radar_state.targets_detected_azimuth[i] < 0.0)
      radar_state.targets_detected_azimuth[i] += 2.0 * T_PI;
    radar_state.targets_detected_distance.push_back(
        radar_state.targets_real_distance[i] + 
        radar_state.targets_error[i].error_overall_distance);
    radar_state.targets_detected_elevation.push_back(
        radar_state.targets_real_elevation[i] +
        radar_state.targets_error[i].error_overall_elevation);
    if (radar_state.targets_detected_elevation[i] > 2.0 * T_PI)
      radar_state.targets_detected_elevation[i] -= 2.0 * T_PI;
    else if (radar_state.targets_detected_elevation[i] < 0.0)
      radar_state.targets_detected_elevation[i] += 2.0 * T_PI;   
    Point2D target;
    CalculateObjectPosition(radar_state.point,
                            radar_state.targets_detected_azimuth[i],
                            cos(radar_state.targets_detected_elevation[i]) *
                            radar_state.targets_detected_distance[i],
                            target);
    radar_state.targets_radar.push_back(target);
    radar_state.targets_radar_height.push_back(
        sin(radar_state.targets_detected_elevation[i]) *
        radar_state.targets_detected_distance[i]);
    
    radar_state.targets_detected_velocity.push_back(
        radar_state.targets_real_velocity[i] *
        (1 + radar_state.targets_error[i].error_overall_distance / 
        radar_state.targets_real_velocity[i]));

    radar_state.targets_filter.push_back(Point2D(
        (radar_state.targets[i].x + 
        radar_state.targets_radar[i].x) / 2.0,
        (radar_state.targets[i].y + 
        radar_state.targets_radar[i].y) / 2.0));

    //TODO: something
    radar_state.targets_error[i].error_distance = 
        radar_state.targets_error[i].error_overall_distance;
    radar_state.targets_error[i].error_velocity =
        radar_state.targets_real_velocity[i] - 
        radar_state.targets_detected_velocity[i];
    radar_state.targets_error[i].error_direction = 
        (radar_state.targets_error[i].error_overall_elevation +
        radar_state.targets_error[i].error_overall_azimuth) / 2.0;
  }
}

void SectorRadar::CalculateObjectPosition(const Point2D& radar,
                                          double azimuth,
                                          double distance,
                                          Point2D& target) {
  target.x = radar.x + cos(FromAngleOfClock2AngleOfCircle(azimuth)) * distance;
  target.y = radar.y + sin(FromAngleOfClock2AngleOfCircle(azimuth)) * distance;
}

void SectorRadar::ClearRadarState(RadarState& radar_state) const {
  radar_state.ids.clear();
  radar_state.targets.clear();
  radar_state.targets_height.clear();
  radar_state.targets_angle_azimuth.clear();
  radar_state.targets_real_distance.clear();
  radar_state.targets_real_elevation.clear();
  radar_state.targets_real_velocity.clear();
  radar_state.targets_real_course.clear();
  radar_state.targets_radar.clear();
  radar_state.targets_radar_height.clear();
  radar_state.targets_detected_azimuth.clear();
  radar_state.targets_detected_distance.clear();
  radar_state.targets_detected_elevation.clear();
  radar_state.targets_detected_velocity.clear();
  radar_state.targets_detected_course.clear();
  radar_state.targets_filter.clear();
  radar_state.targets_error.clear();
}

void SectorRadar::CalculateObjectCourse(RadarState& radar_state) {
  std::map<long long, std::pair<double, double> > real_old_position;
  for (std::size_t i=0; i!=radar_state_last_.ids.size(); ++i)
    real_old_position.insert(std::make_pair(radar_state_last_.ids[i],
        std::make_pair(radar_state_last_.targets[i].x,
        radar_state_last_.targets[i].y)));
  radar_state.targets_real_course.clear();
  for (std::size_t i=0; i!=radar_state.ids.size(); ++i) {
    if (0 == real_old_position.count(radar_state.ids[i])) {
      radar_state.targets_real_course.push_back(0.0);
    } else {
      std::pair<double, double> temp = real_old_position[radar_state.ids[i]];
      radar_state.targets_real_course.push_back(AngleFromStartByClockInCircle(
         temp.first,
         temp.second + 1.0,
         temp.first,
         temp.second,
         radar_state.targets[i].x,
         radar_state.targets[i].y
         ));
    }
  }

  std::map<long long, std::pair<double, double> > detected_old_position;
  for (std::size_t i=0; i!=radar_state_last_.ids.size(); ++i)
    detected_old_position.insert(std::make_pair(radar_state_last_.ids[i],
        std::make_pair(radar_state_last_.targets_radar[i].x,
        radar_state_last_.targets_radar[i].y)));
  radar_state.targets_detected_course.clear();
  for (std::size_t i=0; i!=radar_state.ids.size(); ++i) {
    if (0 == detected_old_position.count(radar_state.ids[i])) {
      radar_state.targets_detected_course.push_back(0.0);
    } else {
      std::pair<double, double> temp = detected_old_position[radar_state.ids[i]];
      radar_state.targets_detected_course.push_back(AngleFromStartByClockInCircle(
         temp.first,
         temp.second + 1.0,
         temp.first,
         temp.second,
         radar_state.targets[i].x,
         radar_state.targets[i].y));
    }
  }
}

} //namespace tools
