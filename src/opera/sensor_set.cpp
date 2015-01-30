#include "sensor_set.h"

namespace tools {

void RadarSet2D::GetState(const TrackSet2D::TrackSetState& track_set_state,
                          RadarSetState& radar_set_state) {
  Radar2D::RadarState radar_state;
  radar_set_state.radar_set_state.clear();
  for (RadarSet::iterator iter = radar_set_->begin();
      iter != radar_set_->end();
      ++iter) {
    (*iter)->GetState(track_set_state, radar_state);
    radar_set_state.radar_set_state.push_back(radar_state);
  }
}

} //namespace tools
