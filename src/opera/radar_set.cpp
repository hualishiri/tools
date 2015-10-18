#include "opera/radar_set.h"
#include "opera_option.h"

#include <iomanip>

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

bool RadarSet2D::RadarSetState::operator==(
    const RadarSetState& radar_set_state) const {
  if (this->radar_set_state.size() != radar_set_state.radar_set_state.size())
    return false;
  for (std::size_t i=0; i!=radar_set_state.radar_set_state.size(); ++i)
    if (!(this->radar_set_state[i] == radar_set_state.radar_set_state[i]))
      return false;
  return true;
}
std::ostream& operator<<(std::ostream& out,
    const RadarSet2D::RadarSetState& radar_set_state) {
  out << std::fixed << std::setprecision(20);
  out << radar_set_state.radar_set_state.size() << " ";    
  for (std::size_t i=0; i!=radar_set_state.radar_set_state.size(); ++i)
    out << radar_set_state.radar_set_state[i] << " "; 
  return out;
}
std::istream& operator>>(std::istream& in,
    RadarSet2D::RadarSetState& radar_set_state) {
  std::size_t length;
  Radar2D::RadarState radar_state;
  in >> length;
  radar_set_state.radar_set_state.clear();
  for (std::size_t i=0; i!=length; ++i) {
    in >> radar_state;
    radar_set_state.radar_set_state.push_back(radar_state);
  }
  return in;
}

void ReadFromFile(std::istream& in, RadarSet2D::RadarSetState& radar_set_state) {
  transform_from_istream_bin_trans(in, radar_set_state.radar_set_state);
}

void WriteToFile(std::ostream& os, const RadarSet2D::RadarSetState& radar_set_state) {
  transform_to_ostream_bin_trans(os, radar_set_state.radar_set_state);
}

} //namespace tools
