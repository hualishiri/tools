#ifndef TOOLS_OPERA_RADAR_H_
#define TOOLS_OPERA_RADAR_H_

#include "opera/sensor.h"

namespace tools {

class Radar2D : public Sensor {
 public:
  struct RadarState {
    long long id;
    Point2D point;
    std::vector<Point2D> targets;
    std::vector<Point2D> targets_radar;
    std::vector<Point2D> targets_filter;
    std::vector<long long> ids;
  };

  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state) = 0;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_H_
