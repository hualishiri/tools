#include "opera/radar_sector.h"

#include "util/tool.h"

namespace tools {

void SectorRadar::GetState(
    const TrackSet2D::TrackSetState& track_set_state,
    RadarState& radar_state) {
  radar_state.id = radar_->id;
  radar_state.type = radar_->type;
  radar_state.point.x = radar_->x;
  radar_state.point.y = radar_->y;
  radar_state.targets.clear();
  radar_state.targets_radar.clear();
  radar_state.targets_filter.clear();
  radar_state.targets_angle_azimuth.clear();
  radar_state.ids.clear();
  for (std::vector<Track2D::TrackState>::const_iterator iter 
      = track_set_state.track_set_state.begin();
      iter != track_set_state.track_set_state.end();
      ++iter) {
    if (IsCaptured(Point2D(radar_->x, radar_->y), iter->point)) {
      std::size_t index = radar_state.targets.size();
      radar_state.targets.push_back(iter->point);  
      radar_state.targets_radar.push_back(iter->point);
      radar_noise_->ApplyNoise(&radar_state.targets_radar[index].x,
                               &radar_state.targets_radar[index].y);
      radar_state.targets_filter.push_back(Point2D(
          (radar_state.targets[index].x + radar_state.targets[index].x) / 2.0,
          (radar_state.targets_radar[index].y 
          + radar_state.targets_radar[index].y) / 2.0));
      radar_state.targets_angle_azimuth.push_back(
          GetAngleOfAzimuth(Point2D(radar_->x, radar_->y), iter->point));
      radar_state.ids.push_back(iter->id);
    }
  }
}

bool SectorRadar::IsCaptured(const Point2D& radar,
                                   const Point2D& target) const {
  double distance = Distance2DArc(radar.x, radar.y, target.x, target.y);
  if (distance >= radar_->distance_detect)
    return false;

  double angle_target_amuzith = GetAngleOfAzimuth(radar, target);
  return IsInRange(radar_->azimuth_range, angle_target_amuzith);
}

float SectorRadar::GetAngleOfAzimuth(const Point2D& radar,
                                     const Point2D& target) const {
  return T_PI - AngleFromStartByClockInCircle(radar.x,
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
  double angle_relative = 0.0;
  for (std::size_t i=0; i!=azimuth_range.size(); ++i) {
    if (target_angle >= azimuth_range[i].first && 
        target_angle <= azimuth_range[i].first + azimuth_range[i].second)
      return true;
  }
  return false;
}

} //namespace tools
