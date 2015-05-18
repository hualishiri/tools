#include "radar_mechanical.h"

#include "opera/radar_noise_gauss.h"
#include "util/logger.h"
#include "util/testharness.h"
#include "util/tool.h"

namespace tools {

class RADAR_MECHANICAL {};

TEST(RADAR_MECHANICAL, GetState) {
  MechanicalRadar2D::Radar radar_internal;
  radar_internal.x = 0.0;
  radar_internal.y = 0.0;
  radar_internal.id = 0x01;
  radar_internal.distance_detect = 20.0;
  radar_internal.level_noise = 10;

  RadarNoiseGauss* radar_noise_gauss 
      = new RadarNoiseGauss(radar_internal.level_noise);

  Radar2D *radar = new MechanicalRadar2D(&radar_internal, radar_noise_gauss);

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
  int len = sizeof(track_states)/sizeof(double) / 2;
  for (int i=0; i != len; ++i) {
    Track2D::TrackState track_state;
    track_state.point = Point2D(track_states[i * 2], track_states[i * 2 + 1]);
    track_set_state.track_set_state.push_back(track_state);
  }
  Radar2D::RadarState radar_state;
  radar->GetState(track_set_state, radar_state);
  for (std::size_t i = 0; i != radar_state.targets.size(); ++i) {
    ASSERT_TRUE(DoubleEqual(radar_state_std[2 * i],
                            radar_state.targets[i].x));
    ASSERT_TRUE(DoubleEqual(radar_state_std[2 * i + 1],
                            radar_state.targets[i].y));
  }
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
