#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdint.h>

#include <vector>
#include <string>

#include "track_set.h"
#include "shape.h"

namespace tools {

class Radar2D {
 public:
  struct RadarState {
    unsigned long long id;
    Point2D point;
    std::vector<Point2D> targets;
  };
  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                        RadarState& radar_state) = 0;
};

class MechanicalRadar2D : public Radar2D {
 public:
  MechanicalRadar2D(unsigned long long id,
                    double x, double y,
                    double max_distance_detect)
    : id_(id), x_(x), y_(y),  max_distance_detect_(max_distance_detect) {
  }

virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
                      RadarState& radar_state);
  
 private:
  bool IsCaptured(const Point2D& radar, const Point2D& target) const;

  unsigned long long id_;
  double x_;
  double y_;
  double max_distance_detect_;
};

}

#endif //SENSOR_H_
