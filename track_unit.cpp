#include "track_unit.h"

#include <cmath>

#include "shape.h"

namespace tools{

long long TrackUnit::GetSumTick(){
  Execute();
  return tick_sum_;
  //calculate the rest distance;
}
float TrackUnit::GetEndSpeed(){
  Execute();
  return speed_end_;
}

void TrackUnit::GetEndPoint(Point2D& point){
  shape_->GetPoint(shape_->GetLength(), point);
}

double TrackUnit::GetSumLength() const{
  return shape_->GetLength();
}

void TrackUnit::Execute(){
  float speed_current = init_speed_;
  long long tick_current = 0;
  double distance_current = 0.0;
  double distance_sum = shape_->GetLength();
  float acc_current = acc_->GetAcceleration(tick_current*interval_);
  double distance_dot = interval_* speed_current; 
  do{
    ++tick_current;
    acc_current = acc_->GetAcceleration(tick_current*interval_);
    speed_current += acc_current*interval_;
    distance_current += distance_dot;
    distance_dot = interval_* speed_current;
  }while( distance_current + distance_dot <  distance_sum );
  tick_sum_ = tick_current + 1;
  speed_end_ = speed_current;
}

TrackUnit::Iterator::Iterator(TrackUnit* track_unit){
  track_unit_ = track_unit;
  interval_ = track_unit_->interval_;
  kTickSum_ = track_unit_->GetSumTick();
  tick_current_ = 0;
  speed_current_ = track_unit_->init_speed_;
  distance_dot_ = speed_current_*interval_;
  distance_current_ = 0.0;
}

bool TrackUnit::Iterator::Valid() const{
  return tick_current_ <= kTickSum_;
}

void TrackUnit::Iterator::Next(){
  if(tick_current_ == kTickSum_ - 1)
    distance_current_ =  track_unit_->shape_->GetLength(); 
  else
    distance_current_ += distance_dot_;
  speed_current_ += interval_*track_unit_->acc_->GetAcceleration(tick_current_*interval_);
  distance_dot_ = speed_current_*interval_;
  ++tick_current_;
}

void TrackUnit::Iterator::Reset(){
  speed_current_ = track_unit_->init_speed_;
  tick_current_ = 0;
  distance_current_ = 0.0;
  distance_dot_ = speed_current_*interval_;
}

void TrackUnit::Iterator::Value(TrackUnitState& track_unit_state) const{
  track_unit_->shape_->GetPoint(distance_current_, track_unit_state.point);
  track_unit_state.speed = speed_current_;
  track_unit_state.tick = tick_current_;
  track_unit_state.acc = track_unit_->acc_->GetAcceleration(tick_current_ * interval_);
  track_unit_state.distance = distance_current_;
}

} //namespace tools
