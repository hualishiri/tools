#ifndef SENSOR_H_
#define SENSOR_H_

#include <vector>
#include <string>

#include <stdint.h>

#include "track_set.h"

namespace tools{

class Point2D;

class Radar2D{
public:
  struct RadarState{
    std::vector<Point2D> targets;
  };
  virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
      RadarState& radar_state) = 0;
};

class MechanicalRadar2D : public Radar2D{
public:
  MechanicalRadar2D(double x, double y, double max_distance_detect)
    :x_(x),
     y_(y),
    max_distance_detect_(max_distance_detect){}

virtual void GetState(const TrackSet2D::TrackSetState& track_set_state,
    RadarState& radar_state);
  
private:
  double x_;
  double y_;
  double max_distance_detect_;

  bool IsCaptured(const Point2D& radar, const Point2D& target) const;
};

}

#endif //SENSOR_H_
