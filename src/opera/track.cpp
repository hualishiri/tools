#include "opera/track.h"

#include <stddef.h>

#include <iomanip>

#include "util/tool.h"

namespace tools {

extern const double T_PI;

bool Equal(long double lhs, long double rhs);

double Track2D::GetLength() const{
  double length = 0.0;
  TrackUnitSet::iterator iter = track_unit_set_->begin();
  for(; iter != track_unit_set_->end(); ++iter){
    length += (*iter)->GetSumLength();
  }
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
  assert(track->track_unit_set_->size() > 0);
  track_ = track;
  interval_ = track_->interval_;
  kTickSum_ = track_->GetSumTick();
  iter_track_ = track_->track_unit_set_->begin();
  iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
  TrackUnit::TrackUnitState track_unit_state;
  tick_current_ = 1;
  iter_track_unit_->Value(track_unit_state_);
  distance_current_ = 0.0;
  origin_current_.x = 0.0;
  origin_current_.y = 0.0;
  last_x_ = 0.0;
  last_y_ = 0.0;
}

Track2D::Iterator::Iterator(const Iterator& iterator) {
  interval_ = iterator.interval_;
  tick_current_ = iterator.tick_current_;
  kTickSum_ = iterator.kTickSum_; 
  distance_current_ = iterator.distance_current_;
  distance_dot_ = iterator.distance_dot_;
  origin_current_ = iterator.origin_current_;
  temp_ = iterator.temp_;
  track_unit_state_ = iterator.track_unit_state_;
  track_ = iterator.track_;
  iter_track_ = iterator.iter_track_;
  iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
  last_x_ = iterator.last_x_;
  last_y_ = iterator.last_y_;
}

Track2D::Iterator& Track2D::Iterator::operator=(const Iterator& iterator) {
  interval_ = iterator.interval_;
  tick_current_ = iterator.tick_current_;
  kTickSum_ = iterator.kTickSum_; 
  distance_current_ = iterator.distance_current_;
  distance_dot_ = iterator.distance_dot_;
  origin_current_ = iterator.origin_current_;
  temp_ = iterator.temp_;
  track_unit_state_ = iterator.track_unit_state_;
  track_ = iterator.track_;
  iter_track_ = iterator.iter_track_;
  if (iter_track_unit_) {
    delete iter_track_unit_;
    iter_track_unit_ = NULL; 
  }
  iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
  last_x_ = iterator.last_x_;
  last_y_ = iterator.last_y_;
  return *this;
}

Track2D::Iterator::~Iterator() {
  delete iter_track_unit_;
}

bool Track2D::Iterator::Valid() const{
  return tick_current_ <= kTickSum_;
}

void Track2D::Iterator::Next(){
  if(iter_track_unit_->Valid()){
    iter_track_unit_->Next();
    if(!iter_track_unit_->Valid()
        && ++iter_track_ != track_->track_unit_set_->end()){
      distance_current_+= (*(iter_track_-1))->GetSumLength();
      (*(iter_track_-1))->GetEndPoint(temp_);
      origin_current_.x += temp_.x;
      origin_current_.y += temp_.y;
      delete iter_track_unit_;
      iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
      iter_track_unit_->Value(track_unit_state_);
    }else if(iter_track_ != track_->track_unit_set_->end()){
      iter_track_unit_->Value(track_unit_state_);
    }
  }
  ++tick_current_;
}

void Track2D::Iterator::Value(TrackState& track_state){
  track_state.id = track_->id_;
  track_state.point.x = origin_current_.x + track_unit_state_.point.x;
  track_state.point.y = origin_current_.y + track_unit_state_.point.y; 
  track_state.height = track_->height_;
  track_state.tick = tick_current_;
  track_state.acc = track_unit_state_.acc;
  track_state.speed =track_unit_state_.speed;
  track_state.distance = distance_current_ + track_unit_state_.distance;
  track_state.azimuth = Azimuth(track_state.point.x - last_x_,
                                track_state.point.y - last_y_);
  track_state.track_type = track_->track_type_;
  last_x_ = track_state.point.x;
  last_y_ = track_state.point.y;
}

void Track2D::Iterator::Reset(){
  tick_current_ = 1;
  distance_current_ = 0.0; 
  origin_current_.x = origin_current_.y = 0;
  iter_track_ = track_->track_unit_set_->begin();
  delete iter_track_unit_;
  iter_track_unit_ = new TrackUnit::Iterator(*iter_track_);
  TrackUnit::TrackUnitState track_unit_state;
  iter_track_unit_->Value(track_unit_state);
  track_unit_state_.point.x = track_unit_state.point.x;
  track_unit_state_.point.y = track_unit_state.point.y;
  track_unit_state_.acc = track_unit_state.acc;
  track_unit_state_.speed = track_unit_state.speed;
  track_unit_state_.distance = track_unit_state.distance;
}

float Track2D::Iterator::Azimuth(float x, float y) const {
  float angle = AngleInCircle(x, -1.0 * y);
  if (angle <= T_PI / 2.0)
    angle = T_PI / 2.0 - angle;
  else
    angle = 5.0 * T_PI / 2.0 - angle;
  return angle;
}


bool Track2D::TrackState::operator==(const TrackState& rhs) const {
  if (this->id == rhs.id &&
      DoubleEqual(this->point.x, rhs.point.x) &&
      DoubleEqual(this->point.y, rhs.point.y) &&
      DoubleEqual(this->height, rhs.height) &&
      this->tick == rhs.tick &&
      DoubleEqual(static_cast<double>(this->acc),
          static_cast<double>(rhs.acc)) &&
      DoubleEqual(static_cast<double>(this->speed),
          static_cast<double>(rhs.speed)) &&
      DoubleEqual(this->distance, rhs.distance) &&
      DoubleEqual(static_cast<double>(this->azimuth),
          static_cast<double>(rhs.azimuth)) &&
      this->track_type == rhs.track_type)
    return true;
  return false;
}

bool Track2D::TrackState::operator!=(const TrackState& rhs) const {
  return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& out,
    const Track2D::TrackState& track_state) {
  out << std::fixed << std::setprecision(20);
  out << track_state.id << " ";
  out << track_state.point.x << " ";
  out << track_state.point.y << " ";
  out << track_state.height<< " ";
  out << track_state.tick << " ";
  out << track_state.acc << " ";
  out << track_state.speed << " ";
  out << track_state.distance << " ";
  out << track_state.azimuth << " ";
  out << track_state.track_type << " ";
  return out;
}

std::istream& operator>>(std::istream& in,
    Track2D::TrackState& track_state) {
  in >> track_state.id;
  in >> track_state.point.x;
  in >> track_state.point.y;
  in >> track_state.height;
  in >> track_state.tick;
  in >> track_state.acc;
  in >> track_state.speed;
  in >> track_state.distance;
  in >> track_state.azimuth;
  in >> track_state.track_type;
  return in;
}

} //namespace tools
