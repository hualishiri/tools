#ifndef TOOLS_OPERA_TRACK_UNIT_H_
#define TOOLS_OPERA_TRACK_UNIT_H_

#include <assert.h>

#include "opera/shape.h"

namespace tools {

class Acceleration;

class TrackUnit {
 public:
  struct TrackUnitState {
    Point2D point;
    unsigned long long tick;
    float acc;
    float speed;
    double distance;
  };

  class Iterator {
   public:
    explicit Iterator(TrackUnit* track_unit);
    bool Valid() const;
    void Next();
    void Reset();
    void Value(TrackUnitState& track_unit_state) const;
   private:
    float interval_;
    float speed_current_;
    long long tick_current_;
    long long kTickSum_;
    double distance_current_;
    double distance_dot_;
    TrackUnit* track_unit_;
  };

  TrackUnit(Shape2D* shape, Acceleration* acc, float interval, float init_speed)
      : init_speed_(init_speed),
        interval_(interval),
        speed_end_(0.0),
        tick_sum_(0),
        shape_(shape),
        acc_(acc) {
    assert(shape && acc);
    assert(interval > 0);
    assert(init_speed >= 0);
  }
  long long GetSumTick();
  float GetEndSpeed();
  void GetEndPoint(Point2D& point);
  double GetSumLength() const;
  Shape2D* shape() const { return shape_; }
  Acceleration* acceleration() const { return acc_; }

 private:
  void Execute();

  float init_speed_;
  float interval_;
  float speed_end_;
  long long tick_sum_;
  Shape2D* shape_;
  Acceleration* acc_;

  friend class Iterator;
};

} //namespace tools

#endif //TOOLS_OPERA_TRACK_UNIT_H_
