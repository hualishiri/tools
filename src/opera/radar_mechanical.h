#ifndef TOOLS_OPERA_RADAR_MECHANICAL_H_
#define TOOLS_OPERA_RADAR_MECHANICAL_H_

#include "opera/radar.h"
#include "opera/track_set.h"

namespace tools {

class MechanicalRadar2D : public Radar2D {
 public:
  MechanicalRadar2D(long long id,
                    double x, double y,
                    double max_distance_detect)
    : id_(id), x_(x), y_(y),  max_distance_detect_(max_distance_detect) {
  }

virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                      RadarState& radar_state);
  
 private:
  bool IsCaptured(const Point2D& radar, const Point2D& target) const;

  long long id_;
  double x_;
  double y_;
  double max_distance_detect_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_MECHANICAL_H_
