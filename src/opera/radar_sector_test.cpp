#include "opera/radar_sector.h"

#include "opera/radar.h"
#include "opera/track_set.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class RADARSECTOR {};

TEST(RADARSECTOR, GetState) {
  SectorRadar::Radar radar;
  radar.id = 0xdeadbeef;
  radar.type = 0;
  radar.x = 1.0;
  radar.y = 1.0;
  radar.height = 13.314312;
  radar.track_id = 0x01;
  radar.azimuth_range.push_back(std::make_pair(0.0, 6.24));
  radar.distance_detect = 20;
  radar.detecting_objects_types = 0x01 | 0x02 | 0x04;

  radar.error_random_azimuth = 0.01;
  radar.error_random_distance = 1.0;
  radar.error_random_elevation = 0.001;
  radar.error_system_azimuth = 0.01;
  radar.error_system_distance = 1.0;
  radar.error_system_elevation = 0.01;

  SectorRadar sector_radar(&radar, NULL);

  TrackSet2D::TrackSetState track_set_state;
  Radar2D::RadarState radar_state;

  Track2D::TrackState track_state;
  track_state.id = 0x02;
  track_state.point.x = 3.0;
  track_state.point.y = 3.0;
  track_state.height = 43.431;
  track_state.tick = 5243;
  track_state.acc = 3.0f;
  track_state.speed = 2.0;
  track_state.azimuth = 3.14;
  track_state.track_type = 0x01 | 0x02 | 0x04;
  
  track_set_state.track_set_state.push_back(track_state);

  sector_radar.GetState(track_set_state, radar_state);
  
  /*LogInfo("Radar ID: 0x%X\n", radar_state.id);
  LogInfo("Radar Position: %f, %f\n\n", radar_state.point.x, radar_state.point.y);
  for (std::size_t i=0; i!=radar_state.ids.size(); ++i) {
    LogInfo("Target ID: %lu\n", radar_state.ids[i]);
    LogInfo("Target Real Positioin: (%f, %f)\n", 
        radar_state.targets[i].x,
        radar_state.targets[i].y);
    LogInfo("Target Angle Azimuth : %f\n", radar_state.targets_angle_azimuth[i]);
    LogInfo("Target Real Distance : %f\n", radar_state.targets_real_distance[i]);
    LogInfo("Target Real Elevation: %f\n", radar_state.targets_real_elevation[i]);
    LogInfo("Target Real Velocity : %f\n\n", radar_state.targets_real_velocity[i]);
        
    LogInfo("Target Radar Position: (%f, %f)\n",
        radar_state.targets_radar[i].x,
        radar_state.targets_radar[i].y);
    LogInfo("Target Radar Azimuth  : %f\n", radar_state.targets_detected_azimuth[i]);
    LogInfo("Target Radar Distance : %f\n", radar_state.targets_detected_distance[i]);
    LogInfo("Target Radar Elevation: %f\n", radar_state.targets_detected_elevation[i]);
    LogInfo("Target Radar Velocity : %f\n\n", radar_state.targets_detected_velocity[i]);

    LogInfo("Target Error Random Distance  : %f\n", 
        radar_state.targets_error[i].error_random_distance);
    LogInfo("Target Error Random Azimuth   : %f\n",
        radar_state.targets_error[i].error_random_azimuth);
    LogInfo("%arget Error Random Elevation : %f\n\n",
        radar_state.targets_error[i].error_random_elevation);
    LogInfo("Target Error System Distance  : %f\n", 
        radar_state.targets_error[i].error_system_distance);
    LogInfo("Target Error System Azimuth   : %f\n",
        radar_state.targets_error[i].error_system_azimuth);
    LogInfo("%arget Error System Elevation : %f\n\n",
        radar_state.targets_error[i].error_system_elevation);
    LogInfo("Target Error Overall Distance  : %f\n", 
        radar_state.targets_error[i].error_overall_distance);
    LogInfo("Target Error Overall Azimuth   : %f\n",
        radar_state.targets_error[i].error_overall_azimuth);
    LogInfo("%arget Error Overall Elevation : %f\n\n",
        radar_state.targets_error[i].error_overall_elevation);
    
  }
  */

}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
