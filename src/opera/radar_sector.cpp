#include "opera/radar_sector.h"

#include "util/tool.h"

namespace tools {
namespace {

double Distance2D(const Point2D& lhs, const Point2D& rhs) {
  return sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2));
}

} //namespace

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
      radar_state.targets.push_back(iter->point);  
      radar_state.ids.push_back(iter->id);
    }
  }
}

bool SectorRadar::IsCaptured(const Point2D& radar,
                                   const Point2D& target) const {
  double distance = Distance2D(radar, target);
  if (distance >= radar_->distance_detect)
    return false;
  double angle_target_amuzith = AngleFromStartByClockInCircle(radar.x,
                                                              radar.y + 1.0,
                                                              radar.x,
                                                              radar.y,
                                                              target.x,
                                                              target.y);
  angle_target_amuzith -= radar_->angle_azimuth;
  if (angle_target_amuzith < 0.0)
    angle_target_amuzith += 2 * M_PI;
  if (angle_target_amuzith < radar_->angle_sector_range)
    return true;
  return false;
}

} //namespace tools
