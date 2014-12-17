#ifndef TOOLS_TRACK_UNIT_H_
#define TOOLS_TRACK_UNIT_H_

#include "shape.h"

namespace tools{

class Shape2D;
class Acceleration;
class PointState2D;

class Acceleration{
public:
  virtual float GetAcceleration(unsigned long time) const = 0;
};

class UniformAcceleration : public Acceleration{
public:
  float GetAcceleration(unsigned long time) const{ return 0.0; }
};

class ConstantAcceleration : public Acceleration{
public:
  explicit ConstantAcceleration(float acc) : acc_(acc){}
  float GetAcceleration(unsigned long time) const{ return acc_; }
private:
  const float acc_; };

class VariableAcceleration : public Acceleration{
public:
  explicit VariableAcceleration(float (*func)(unsigned long)) : acc_(func){}
  float GetAcceleration(unsigned long time) const{ return acc_(time); }
private:
  float (*acc_)(unsigned long);
};

class TrackUnit{
public:
  struct TrackUnitState{
    Point2D point;
    unsigned long long tick;
    float acc;
    float speed;
    double distance;
  };
  class Iterator{
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
    :shape_(shape), acc_(acc), interval_(interval), speed_end_(0.0), tick_sum_(0),
    init_speed_(init_speed){}
  long long GetSumTick();
  float GetEndSpeed();
  void GetEndPoint(Point2D& point);
  double GetSumLength() const;
private:
  float init_speed_;
  float interval_;
  Shape2D* shape_;
  Acceleration* acc_;

  float speed_end_;
  long long tick_sum_;

  void Execute();
  friend class Iterator;
};
} //namespace tools

#endif //TOOLS_TRACK_UNIT_H_
