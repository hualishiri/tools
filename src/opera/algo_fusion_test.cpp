#include "opera/algo_fusion.h"

#include <iomanip>

#include "opera/radar.h"
#include "util/testharness.h"

namespace tools {

class ALGOFUSION {};

TEST(ALGOFUSION, Handle) {
  std::size_t count = 20;
  std::vector<Radar2D::RadarState> radar_set_state;

  for (std::size_t i=0; i!=count; ++i) {
    Radar2D::RadarState radar_state;
    radar_state.id = i; 
    radar_state.point.x = 1.0;
    radar_state.point.x = 2.0;

    for (std::size_t j=0; j!= 20; ++j) {
      radar_state.ids.push_back(i * j);
      Point2D point;
      point.x = point.y = static_cast<double>(j);
      radar_state.targets.push_back(point);
      radar_state.targets_angle_azimuth.push_back(1.0 * i * j);
      radar_state.targets_real_distance.push_back(1.0 * i * j);
      radar_state.targets_real_elevation.push_back(1.0 * i * j);
      radar_state.targets_real_velocity.push_back(1.0 * i * j);

      point.x = point.y = static_cast<double>(1.0 * i * j);
      radar_state.targets_radar.push_back(point);
      radar_state.targets_detected_azimuth.push_back(1.0 * i * j);
      radar_state.targets_detected_distance.push_back(1.0 * i * j);
      radar_state.targets_detected_elevation.push_back(1.0 * i * j);
      radar_state.targets_detected_velocity.push_back(1.0 * i * j);
      Radar2D::RadarError radar_error;
      radar_state.targets_error.push_back(radar_error);
      radar_set_state.push_back(radar_state);
    }
  }

  std::vector<AlgoFusion::FusionTarget> fusion_set_target;
  AlgoFusion::Input input;
  input.radar_set_state = &radar_set_state;
  AlgoFusion::Output output;
  output.targets = &fusion_set_target;

  AlgoFusion algo_fusion;
  algo_fusion.Handle((void*)&input, (void*)&output);
}

} //namespace toosl

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
