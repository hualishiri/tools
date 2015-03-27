#include "opera/radar_mechanical.h"

#include "opera/radar_noise.h"
#include "util/logger.h"
#include "util/tool.h"

namespace tools {
namespace {

double Distance2D(const Point2D& lhs, const Point2D& rhs) {
  return sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2));
}

} //namespace

void MechanicalRadar2D::GetState(
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
      int index = radar_state.targets.size();
      radar_state.targets.push_back(iter->point);  
      radar_state.ids.push_back(iter->id);
      radar_state.targets_radar.push_back(iter->point);
      radar_noise_->ApplyNoise(&radar_state.targets_radar[index].x,
                               &radar_state.targets_radar[index].y);
      radar_state.targets_filter.push_back(Point2D(
          (radar_state.targets[index].x + radar_state.targets_radar[index].x) / 2.0,
          (radar_state.targets[index].y 
          + radar_state.targets_radar[index].y) / 2.0));
      radar_state.ids.push_back(iter->id);
      index = radar_state.targets.size();
      LogInfo("Object NUMBER: %d", radar_state.targets.size());
    }
  }
}

bool MechanicalRadar2D::IsCaptured(const Point2D& radar,
                                   const Point2D& target) const {
  double distance = Distance2D(radar, target);
  if (distance <= radar_->distance_detect)
    return true;
  return false;
}

} //namespace tools
