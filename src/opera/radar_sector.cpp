#include "opera/radar_sector.h"

#include "util/tool.h"

namespace tools {

void SectorRadar::GetState(
    const TrackSet2D::TrackSetState& track_set_state,
    RadarState& radar_state) {
  radar_state.id = radar_->id;
  radar_state.point.x = radar_->x;
  radar_state.point.y = radar_->y;
  radar_state.targets.clear();
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
  angle_target_amuzith -= radar_->angle_azimuth;
  if (angle_target_amuzith < 0.0)
    angle_target_amuzith += 2 * T_PI;
  if (angle_target_amuzith < radar_->angle_sector_range)
    return true;
  return false;
}

float SectorRadar::GetAngleOfAzimuth(const Point2D& radar,
                                     const Point2D& target) const {
  return 2.0 * T_PI - AngleFromStartByClockInCircle(radar.x,
                                       radar.y - 1.0,
                                       radar.x,
                                       radar.y,
                                       target.x,
                                       target.y);
}

} //namespace tools
