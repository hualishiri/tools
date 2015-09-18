#ifndef TOOLS_OPERA_RADAR_SET_H_
#define TOOLS_OPERA_RADAR_SET_H_

#include <vector>

#include "opera/radar.h"

namespace tools {

class RadarSet2D {
 public:
  struct RadarSetState {
    std::vector<Radar2D::RadarState> radar_set_state;

    bool operator==(const RadarSetState& radar_set_state) const;
    friend std::ostream& operator<<(std::ostream& out,
        const RadarSetState& radar_set_state);
    friend std::istream& operator>>(std::istream& in,
        RadarSetState& radar_set_state);
  };
  typedef std::vector<Radar2D*> RadarSet;

  RadarSet2D(RadarSet* radar_set) : radar_set_(radar_set) {}
  void GetState(const TrackSet2D::TrackSetState& track_set_state,
                RadarSetState& radar_set_state);
  RadarSet* radar_set() const { return radar_set_; }

 private:
  RadarSet* radar_set_;
};

} //namespace tools

#endif //TOOLS_OPERA_RADAR_SET_H_
