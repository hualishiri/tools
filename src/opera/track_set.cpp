#include "opera/track_set.h"

#include <stdlib.h>

namespace tools {

long long TrackSet2D::GetSumTick() const{
  long long sum_tick = 0;
  long long temp = 0;
  for (std::size_t i=0; i!=rep_track_set_->size(); ++i) {
    temp = (*rep_track_set_)[i]->GetSumTick() + (*track_set_delay_)[i];
    if (temp > sum_tick)
      sum_tick = temp;
  }
  return sum_tick;
}

double TrackSet2D::GetSumLength() const{
  double sum_length = 0.0;
  double temp = 0.0;
  for(TrackSet::iterator iter = rep_track_set_->begin();
      iter != rep_track_set_->end(); ++iter){
    temp = (*iter)->GetLength();
    if(temp > sum_length)
      sum_length = temp;
  }
  return sum_length;
}

const Point2D& TrackSet2D::GetInitPosition(long long id) const{
    TrackSet::iterator iter_track_set = rep_track_set_->begin();
    for(std::size_t i = 0; i!= rep_track_set_->size(); ++i){
      if((*rep_track_set_)[i]->id() == id)
        return *(*track_set_init_pos_)[i];
    }
    return *(*track_set_init_pos_)[-1];
}

void TrackSet2D::Iterator::PositionChange(const TrackSetPosition& pos, 
    TrackSetState& track_set_state){
    TrackSetPosition::const_iterator iter = pos.begin();
    std::vector<Track2D::TrackState>::iterator iter_state 
      = track_set_state.track_set_state.begin();
    while(iter_state != track_set_state.track_set_state.end()){
      iter_state->point.x += track_set_->GetInitPosition(iter_state->id).x;
      iter_state->point.y += track_set_->GetInitPosition(iter_state->id).y;
      ++iter;
      ++iter_state;
    }
}

TrackSet2D::Iterator::Iterator(TrackSet2D* track_set){
  track_set_ = track_set;
  rep_track_set_ = track_set_->rep_track_set_;
  count_invalid_track_ = rep_track_set_->size();
  track_set_iter_ = new TrackSetIterator();
  track_set_delay_ = track_set->track_set_delay_;
  tick_current_ = 0;
  for(std::size_t i = 0; i != count_invalid_track_; ++i)
    track_set_iter_->push_back(Track2D::Iterator((*rep_track_set_)[i]));
}

TrackSet2D::Iterator::Iterator(const Iterator& iterator) {
  track_set_ = iterator.track_set_;
  rep_track_set_ = iterator.rep_track_set_;
  count_invalid_track_ = iterator.count_invalid_track_;
  track_set_iter_ = new TrackSetIterator();
  *track_set_iter_ = *(iterator.track_set_iter_);
  track_set_delay_ = iterator.track_set_delay_;
  tick_current_ = iterator.tick_current_;
  track_set_iter_ = iterator.track_set_iter_;
}

TrackSet2D::Iterator& TrackSet2D::Iterator::operator=(const Iterator& iterator) {
  track_set_ = iterator.track_set_;
  rep_track_set_ = iterator.rep_track_set_;
  count_invalid_track_ = iterator.count_invalid_track_;
  if (track_set_iter_) {
    delete track_set_iter_;
    track_set_iter_ = NULL;
  }
  track_set_iter_ = new TrackSetIterator();
  *track_set_iter_ = *(iterator.track_set_iter_);
  track_set_delay_ = iterator.track_set_delay_;
  tick_current_ = iterator.tick_current_;
  track_set_iter_ = iterator.track_set_iter_;
  return *this;
}

TrackSet2D::Iterator::~Iterator(){
  if (track_set_iter_ != NULL) {
    delete track_set_iter_;
    track_set_iter_ = NULL;
  }
}

bool TrackSet2D::Iterator::Valid() const{
  return count_invalid_track_ > 0;
}

void TrackSet2D::Iterator::Next(){
  std::size_t i = 0;
  for (TrackSetIterator::iterator iter = track_set_iter_->begin();
      iter != track_set_iter_->end();
      ++iter) {
    if (iter->Valid() && tick_current_ >= (*track_set_delay_)[i]){ 
      iter->Next();
      if (!iter->Valid()) --count_invalid_track_;
    }
    ++i;
  }
  ++tick_current_;
}

void TrackSet2D::Iterator::Value(TrackSetState& track_set_state){
  track_set_state.track_set_state.clear();
  Track2D::TrackState track_state;
  std::size_t i = 0;
  for(TrackSetIterator::iterator iter = track_set_iter_->begin();
      iter != track_set_iter_->end(); ++iter) {
    if(iter->Valid() && tick_current_ >= (*track_set_delay_)[i]){
      iter->Value(track_state);
      track_set_state.track_set_state.push_back(track_state);
    }
    ++i;
  }
  PositionChange(*(track_set_->track_set_init_pos_), track_set_state);
}

void TrackSet2D::Iterator::Reset(){
  tick_current_ = 0;
  count_invalid_track_ = rep_track_set_->size();
  if (track_set_iter_ != NULL) {
    delete track_set_iter_;
    track_set_iter_ = NULL;
  }
  track_set_iter_ = new TrackSetIterator();
  for(std::size_t i = 0; i != count_invalid_track_; ++i)
    track_set_iter_->push_back(Track2D::Iterator((*rep_track_set_)[i]));
}


} //namespace tools
