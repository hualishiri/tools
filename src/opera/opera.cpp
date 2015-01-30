#include "opera.h"

namespace tools {

long long Opera2D::GetSumTick() const {
  return track_set_->GetSumTick();
}

Opera2D::Iterator::Iterator(Opera2D* opera) {
  opera_ = opera;
  iter_track_set_ = new TrackSet2D::Iterator(opera_->track_set_);
}

Opera2D::Iterator::~Iterator() {
  delete iter_track_set_;
}

bool Opera2D::Iterator::Valid() const {
  return iter_track_set_->Valid();
}

void Opera2D::Iterator::Next() {
  iter_track_set_->Next();
}

void Opera2D::Iterator::Value(OperaState& opera_state) {
  iter_track_set_->Value(opera_state.track_set_state);
  opera_->radar_set_->GetState(opera_state.track_set_state, 
                               opera_state.radar_set_state);
}

void Opera2D::Iterator::Reset() {
  iter_track_set_->Reset();
}

} //namespace tools
