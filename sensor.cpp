#include "sensor.h"

#include <cmath>

namespace tools{

double Distance2D(const Point2D& lhs, const Point2D& rhs){
  return sqrt(pow(lhs.x-rhs.x, 2) + pow(lhs.y - rhs.y, 2));
}

void MechanicalRadar2D::GetState(const TrackSet2D::TrackSetState& track_set_state,
    RadarState& radar_state){
  radar_state.id = id_;
  radar_state.targets.clear();
  for(std::vector<Track2D::TrackState>::const_iterator iter 
      = track_set_state.track_set_state.begin();
      iter != track_set_state.track_set_state.end(); ++iter){
    if(IsCaptured(Point2D(x_, y_), iter->point))
      radar_state.targets.push_back(iter->point);  
  }
}

bool MechanicalRadar2D::IsCaptured(const Point2D& radar, const Point2D& target) const{
  double distance = Distance2D(radar, target);
  if(distance <= max_distance_detect_)
    return true;
  return false;
}

} //namespace tools

