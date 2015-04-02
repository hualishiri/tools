#include "opera/opera.h"

#include <iomanip>

#include "opera/opera_option.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class OPERA {};

TEST(OPERA, Iterator) {
  const int len = 4;
  double location_wgs[len] = {
    //-87.65005229999997, 41.850033, 
    //114.1223784, 22.3700556
    0.0, 0.0,
    4.0, 4.0
  };

  tools::OperaOption::Radar radar;
  radar.id = 0x012341;
  //radar.start_x = -87.6500522999999;
  radar.start_x = 2.5;
  //radar.start_y = 41.850033;
  radar.start_y = 2.5;
  //radar.radius_x = 10.134189;
  radar.radius_x = 3.0;
  //radar.radius_y = 30.102435;
  radar.radius_y = 1.0;
  radar.angle_azimuth = 0.0;
  radar.angle_sector_range = 2 * 3.14;
  radar.level_noise = 100;

  tools::OperaOption::Track track;
  tools::OperaOption::Line line = {
    0x1428,
    location_wgs[0], location_wgs[1],
    location_wgs[2], location_wgs[3]
  };

  track.lines.push_back(line);
  track.types.push_back(tools::OperaOption::LINE);
  track.ids.push_back(0x14310);
  track.ids.push_back(0x14311);
  track.ids.push_back(0x14312);
  track.ids.push_back(0x14313);
  track.batch_count = 4;
  track.acceleration = 0;
  track.start_speed = 0.1;
  track.time_delay = 5;
  track.level_noise_track = 0.1;

  tools::OperaOption::Instance()->push_back_radar(radar);
  tools::OperaOption::Instance()->push_back_track(track);
  tools::OperaOption::Instance()->set_interval(1.0);

  Opera2D opera;
  //tools::OperaOption::Instance()->ConvertToPixel();
  opera.Initialize(*(OperaOption::Instance()));
  Opera2D::Iterator iter(&opera);
  Opera2D::OperaState *opera_state = new Opera2D::OperaState();

  while(iter.Valid()) {
    iter.Value(*opera_state);
      //opera_state->ConvertToWgs();
        LogInfo("radar size: %d",
            opera_state->radar_set_state.radar_set_state.size());
        LogInfo("object size: %d",
            opera_state->radar_set_state.radar_set_state[0].targets.size());

        for(std::size_t i = 0;
            i != opera_state->radar_set_state.radar_set_state.size();
            ++i) {
          LogDebug("radar id : %d",
              opera_state->radar_set_state.radar_set_state[i].id);
          for (std::size_t j = 0;
              j != opera_state
              ->radar_set_state.radar_set_state[i].targets.size();
              ++j) {
            LogDebug(
                "object real position : (%f, %f)",
                opera_state->radar_set_state.radar_set_state[i].targets[j].x,
                opera_state->radar_set_state.radar_set_state[i].targets[j].y);
            LogDebug(
                "object noised position : (%f, %f)",
                opera_state->radar_set_state
                    .radar_set_state[i].targets_radar[j].x,
                opera_state->radar_set_state
                    .radar_set_state[i].targets_radar[j].y);
            LogDebug(
                "object filtered position : (%f, %f)",
                opera_state->radar_set_state
                    .radar_set_state[i].targets_filter[j].x,
                opera_state->radar_set_state.
                    radar_set_state[i].targets_filter[j].y);
            LogDebug("Object Azimuth Angle : %f",
                     opera_state->radar_set_state
                        .radar_set_state[i].targets_angle_azimuth[j]);
          }
        }

        for(std::size_t i = 0;
            i!= opera_state->track_set_state.track_set_state.size();
            ++i) {
          std::stringstream streamTemp;
          streamTemp << "updateObject("
              << opera_state->track_set_state.track_set_state[i].id
              << ", " << "0, "
              << std::setprecision(9)
              << opera_state->track_set_state.track_set_state[i].point.x
              << ", "
              << std::setprecision(9)
              << opera_state->track_set_state.track_set_state[i].point.y << ", "
              << opera_state->track_set_state.track_set_state[i].acc << ", "
              << opera_state->track_set_state.track_set_state[i].speed << ", "
              << opera_state->track_set_state.track_set_state[i].azimuth << ");";
            LogInfo("%s", streamTemp.str().c_str());
            streamTemp.clear();
        }
    iter.Next();
  }
  opera.Release();
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
