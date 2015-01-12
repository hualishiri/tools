#ifndef TOOLS_SENSOR_SET_H_
#define TOOLS_SENSOR_SET_H_

#include "track_set.h"
#include "sensor.h"

namespace tools{

class RadarSet2D{
public:
  struct RadarSetState{
    std::vector<Radar2D::RadarState> radar_set_state;
  };
  typedef std::vector<Radar2D*> RadarSet;
  void GetState(const TrackSet2D::TrackSetState& track_set_state,
      RadarSetState& radar_set_state);
  RadarSet2D(RadarSet* radar_set):radar_set_(radar_set){}
private:
  RadarSet* radar_set_;
};

} //namespace tools

#endif //TOOLS_SENSOR_SET_H_
