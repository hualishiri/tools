#include "opera/opera.h"

#include <string.h>

#include <iomanip>
#include <iostream>
#include <sstream>

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
  radar.type = OperaOption::R_STATIC;
  radar.start_x = 2.5;
  //radar.start_y = 41.850033;
  radar.start_y = 2.5;
  //radar.radius_x = 10.134189;
  radar.radius_x = 3.0;
  //radar.radius_y = 30.102435;
  radar.radius_y = 1.0;
  radar.azimuth_range.push_back(std::make_pair(0.0, 3.14));
  radar.azimuth_range.push_back(std::make_pair(3.14, 3.14));

  radar.error.error_random_distance = 1.0;
  radar.error.error_random_azimuth = 0.001;
  radar.error.error_random_elevation = 0.001;
  radar.error.error_system_distance = 1.0;
  radar.error.error_system_azimuth = 0.001;
  radar.error.error_system_elevation = 0.001;

  radar.detecting_objects_types = 
      OperaOption::AIRCRAFT | OperaOption::LANDCRAFT | OperaOption::UNDERCRAFT;

  tools::OperaOption::Track track;
  tools::OperaOption::Line line = {
    0x1428,
    location_wgs[0], location_wgs[1],
    location_wgs[2], location_wgs[3]
  };

  track.id = 103;
  track.lines.push_back(line);
  track.types.push_back(tools::OperaOption::LINE);
  track.ids.push_back(0x14310);
  track.ids.push_back(0x14311);
  track.ids.push_back(0x14312);
  track.ids.push_back(0x14313);
  track.batch_count = 4;

  std::size_t size_batch = static_cast<std::size_t>(track.batch_count);
  for (std::size_t i=0; i!=size_batch; ++i) {
    std::vector<double> acc;
    track.accelerations.push_back(acc);
    for (std::size_t j=0; j!=track.types.size(); ++j)
      track.accelerations[i].push_back(0);
    track.start_speeds.push_back(0.1);
    track.time_delays.push_back(5);
    track.track_types.push_back(
      OperaOption::AIRCRAFT | OperaOption::LANDCRAFT | OperaOption::UNDERCRAFT);
      //0);
  }

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
      for(std::size_t i = 0;
          i != opera_state->radar_set_state.radar_set_state.size();
          ++i) {
        for (std::size_t j = 0;
            j != opera_state
            ->radar_set_state.radar_set_state[i].targets.size();
            ++j) {
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
          streamTemp.clear();
        }
    iter.Next();
  }
  opera.Release();
  delete opera_state;
}

TEST(OPERA, OperaState) {
  Opera2D::OperaState opera_state;
  Track2D::TrackState track_state;

  for (std::size_t i=0; i!=5; ++i) {
    track_state.id = i+1;
    track_state.point.x = 128.341;
    track_state.point.y = 18.4114;
    track_state.tick = 41243124;
    track_state.acc = 4.14312;
    track_state.speed = 1.43124;
    track_state.distance = 43.43124312;
    track_state.azimuth = 23.414312;
    opera_state.track_set_state.track_set_state.push_back(track_state);
  }

  Radar2D::RadarState radar_state;
  for (std::size_t i=0; i!=5; ++i) {
    radar_state.id = i + 20;
    radar_state.point.x = 12.34141;
    radar_state.point.y = 34.4132412;
    for (std::size_t j=0; j!=3; ++j) {
      radar_state.targets.push_back(Point2D(23.2412, 28.9841));
      radar_state.targets_radar.push_back(Point2D(2.43122, 8.843141));
      radar_state.targets_filter.push_back(Point2D(42.2412, 31.9841));
      radar_state.ids.push_back(j*j);
      radar_state.targets_angle_azimuth.push_back(28.431243);
    }
    opera_state.radar_set_state.radar_set_state.push_back(radar_state);
  }

  std::ostringstream ostrstream;
  ostrstream << opera_state;

  std::istringstream istrstream(ostrstream.str().c_str());
  Opera2D::OperaState opera_state_temp;
  istrstream >> opera_state_temp;
  std::ostringstream ostrstream_temp;
  ostrstream_temp << opera_state_temp;
  assert(0 == strcmp(ostrstream.str().c_str(), ostrstream_temp.str().c_str()));
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
