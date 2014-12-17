#include "track.h"

#include <cassert>

#include "track_unit.h"

namespace tools{

bool Equal(long double lhs, long double rhs){
  if((lhs - rhs < 0.0000001) && (lhs - rhs > -0.00000001))
    return true;
  else
    return false;
}

double Track2D::GetLength() const{
  double length = 0.0;
  TrackUnitSet::iterator iter = track_unit_set_->begin();
  for(; iter != track_unit_set_->end(); ++iter)
    length += (*iter)->GetSumLength();
	return length;
}

long long Track2D::GetSumTick() const{
	long long sum_tick = 0;
  TrackUnitSet::iterator iter = track_unit_set_->begin();
  for(; iter != track_unit_set_->end(); ++iter)
    sum_tick += (*iter)->GetSumTick();
	return sum_tick;
}

Track2D::Iterator::Iterator(Track2D* track){
  track_ = track_;
  interval_ = track_->interval_;
  kTickSum_ = track_->GetSumTick();
  tick_current_ = 0;
  speed_current_ = track_->init_speed_;
  distance_current_ = 0.0;
  iter_track_ = track_->track_unit_set_->begin();
  iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
  origin_current_.x = 0.0;
  origin_current_.y = 0.0;
}

bool Track2D::Iterator::Valid() const{
  return tick_current_ <= kTickSum_;
}

void Track2D::Iterator::Next(){
  if(iter_track_ != track_->track_unit_set_->end()){
    if(!iter_track_unit_->Valid()){
      distance_current_ += (*iter_track_)->GetSumLength();
      (*iter_track_)->GetEndPoint(temp_);
      origin_current_.x += temp_.x;
      origin_current_.y += temp_.y;
      delete iter_track_unit_;
      ++iter_track_;
      iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
      iter_track_unit_->Next();
    }
    iter_track_unit_->Value(track_unit_state_);
    speed_current_ = track_unit_state_.speed;
    ++tick_current_;
    iter_track_unit_->Next();
  }
}

void Track2D::Iterator::Value(TrackState& track_state) const{
  track_state.point.x = origin_current_.x + track_unit_state_.point.x;
  track_state.point.y = origin_current_.y + track_unit_state_.point.y;
  track_state.tick = tick_current_;
  track_state.acc = track_unit_state_.acc;
  track_state.speed =track_unit_state_.speed;
  track_state.distance = distance_current_ + track_unit_state_.distance;
}

void Track2D::Iterator::Reset(){
  tick_current_ = 0;
  distance_current_ = 0; 
  origin_current_.x = origin_current_.y = 0;
  iter_track_ = track_->track_unit_set_->begin();
  iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
}

} //namespace tools
