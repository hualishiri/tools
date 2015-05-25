#ifndef TOOLS_OPERA_RADAR_H_
#define TOOLS_OPERA_RADAR_H_

#include "opera/sensor.h"

namespace tools {

class Radar2D : public Sensor {
 public:
  struct RadarState {
    long long id;
    int type;
    Point2D point;
    std::vector<Point2D> targets;
    std::vector<Point2D> targets_radar;
    std::vector<Point2D> targets_filter;
    std::vector<float> targets_angle_azimuth;
    std::vector<long long> ids;
  };

  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state) = 0;
  virtual void SetPosition(double x, double y) = 0;
  virtual long long id() const = 0;
  virtual int type() const = 0;
  virtual long long track_id() const = 0;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_H_
