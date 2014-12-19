#include "track_set.h"

namespace tools{

TrackSet2D::Iterator::Iterator(TrackSet2D* track_set){
  track_set_ = track_set;
  rep_track_set_ = track_set_->rep_track_set_;
  count_invalid_track_ = rep_track_set_->size();
  track_set_iter_ = new TrackSetIterator();
  for(std::size_t i = 0; i != count_invalid_track_; ++i)
    track_set_iter_->push_back(Track2D::Iterator((*rep_track_set_)[i]));
}

bool TrackSet2D::Iterator::Valid() const{
  return count_invalid_track_ > 0;
}

void TrackSet2D::Iterator::Next(){
  for(TrackSetIterator::iterator iter = track_set_iter_->begin();
      iter != track_set_iter_->end(); ++iter)
    if(iter->Valid()){ 
      iter->Next();
      if(!iter->Valid()) --count_invalid_track_;
    }
}

void TrackSet2D::Iterator::Value(TrackSetState& track_set_state){
  track_set_state.track_set_state.clear();
  Track2D::TrackState track_state;
  for(TrackSetIterator::iterator iter = track_set_iter_->begin();
      iter != track_set_iter_->end(); ++iter)
    if(iter->Valid()){
      iter->Value(track_state);
      track_set_state.track_set_state.push_back(track_state);
    }
}

void TrackSet2D::Iterator::Reset(){
  count_invalid_track_ = rep_track_set_->size();
  delete track_set_iter_;
  track_set_iter_ = new TrackSetIterator();
  for(std::size_t i = 0; i != count_invalid_track_; ++i)
    track_set_iter_->push_back(Track2D::Iterator((*rep_track_set_)[i]));
}

TrackSet2D::Iterator::~Iterator(){
  delete track_set_iter_;
}

} //namespace tools
