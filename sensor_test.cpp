#include "sensor.h"

#include <iostream>
#include <iomanip>
#include <cassert>

#include "track_set.h"
#include "track.h"

namespace tools{
namespace test{

bool Equal(double, double);

class Test{
public:
  void RunAllTest(){
    FunctionTest1();
  }

  void FunctionTest1(){
    Radar2D *radar = new MechanicalRadar2D(0x1, 0.0, 0.0, 20.0);
    double track_states[] = {0.3, 0.5, 
    1.5, 2.3, 
    3.7, 4.8,
    5.9, 6.10,
    7.4, 8.3,
    -1.9, -1.4,
    -1.3, -2.5,
    30.0, 30.0,
    1.0, 2.0};
    double radar_state_std[] = {
      0.3, 0.5,
      1.5, 2.3,
      3.7, 4.8,
      5.9, 6.10,
      7.4, 8.3,
      -1.9, -1.4,
      -1.3, -2.5,
      1.0, 2.0
    };
    TrackSet2D::TrackSetState track_set_state;
    int len = sizeof(track_states)/sizeof(double)/2;
    for(int i=0; i != len; ++i){
      Track2D::TrackState track_state;
      track_state.point = Point2D(track_states[i*2], track_states[i*2+1]);
      track_set_state.track_set_state.push_back(track_state);
    }
    Radar2D::RadarState radar_state;
    radar->GetState(track_set_state, radar_state);
    for(std::size_t i=0; i!=radar_state.targets.size(); ++i){
      assert(Equal(radar_state_std[2*i], radar_state.targets[i].x));
      assert(Equal(radar_state_std[2*i+1], radar_state.targets[i].y));
    }
  }
};

bool Equal(double lhs, double rhs){
  if( lhs - rhs < 0.00000000001 && lhs - rhs > -0.00000000001 )
    return true;
  return false;
}

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
  return 0;
}
