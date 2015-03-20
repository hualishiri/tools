#ifndef TOOLS_OPERA_RADAR_SET_H_
#define TOOLS_OPERA_RADAR_SET_H_

#include <vector>

#include "opera/radar.h"

namespace tools {

class RadarSet2D {
 public:
  struct RadarSetState {
    std::vector<Radar2D::RadarState> radar_set_state;
  };
  typedef std::vector<Radar2D*> RadarSet;

  RadarSet2D(RadarSet* radar_set) : radar_set_(radar_set) {}
  void GetState(const TrackSet2D::TrackSetState& track_set_state,
                RadarSetState& radar_set_state);

 private:
  RadarSet* radar_set_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_SET_H_
