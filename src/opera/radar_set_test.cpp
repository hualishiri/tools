#include "opera/radar_set.h"

#include "opera/radar_mechanical.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class RADARSET {};

TEST(RADARSET, GetState) {
  /*Radar2D* radar1 = new MechanicalRadar2D(0x1, 0.0, 0.0, 10);   
  Radar2D* radar2 = new MechanicalRadar2D(0x2, 0.0, 10.0, 10);   
  Radar2D* radar3 = new MechanicalRadar2D(0x3, 0.0, 5.0, 10);   

  RadarSet2D::RadarSet rep_radar_set;
  rep_radar_set.push_back(radar1);
  rep_radar_set.push_back(radar2);
  rep_radar_set.push_back(radar3);
    
  RadarSet2D radar_set(&rep_radar_set);

  double track_states[] = {
    0.3, 0.5, 
    1.5, 2.3, 
    3.7, 4.8,
    5.9, 6.10,
    7.4, 8.3,
    -1.9, -1.4,
    -1.3, -2.5,
    30.0, 30.0,
    1.0, 2.0
  };
  TrackSet2D::TrackSetState track_set_state;
  int len = sizeof(track_states) / sizeof(double) / 2;
  for (int i=0; i != len; ++i){
    Track2D::TrackState track_state;
    track_state.point = Point2D(track_states[i * 2], track_states[i * 2 + 1]);
    track_state.id = i;
    track_set_state.track_set_state.push_back(track_state);
  }
  RadarSet2D::RadarSetState radar_set_state;
  Radar2D::RadarState radar_state;
  radar_set.GetState(track_set_state, radar_set_state);
  
  for (std::size_t j = 0; j != radar_set_state.radar_set_state.size(); ++j) {
    LogDebug("Radar ID : [%d] And the Radars It Detected:",
             radar_set_state.radar_set_state[j].id);
    for (std::size_t i=0;
        i!=radar_set_state.radar_set_state[j].targets.size();
        ++i) {
      LogDebug("Object ID: 0x%X\tPosition : (%f,%f)",
               radar_set_state.radar_set_state[j].ids[i],
               radar_set_state.radar_set_state[j].targets[i].x,
               radar_set_state.radar_set_state[j].targets[i].y);
    }
  }*/
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
