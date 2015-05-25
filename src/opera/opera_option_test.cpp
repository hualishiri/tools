#include "opera/opera_option.h"

#include <string.h>

#include <sstream>
#include <iostream>

#include "util/testharness.h"

namespace tools {

class OPERAOPTION {};

TEST(OPERAOPTION, PushBack) {
  OperaOption opera_option;
    for (int i = 1; i != 10; ++i) {
      OperaOption::Radar radar;
      radar.id = i;
      radar.type = OperaOption::R_STATIC;
      radar.start_x = 32.32;
      radar.start_y = 15.32;
      radar.radius_x = 98.321;
      radar.radius_y = 19.1342;
      radar.error_system = 1.321;
      radar.error_random = 3.31;
      radar.error_overall = 9.21341;
      radar.azimuth_range.push_back(std::make_pair(14.0, 50.0));
      opera_option.push_back_radar(radar);
    }
    opera_option.pop_radar(2);
    ASSERT_TRUE(opera_option.size_radar() == 8);
    opera_option.pop_radar(15);
    ASSERT_TRUE(opera_option.size_radar() == 8);

    for (int i = 1; i != 10; ++i) {
      OperaOption::Object object;
      object.id = i;
      opera_option.push_back_object(object);
    }
    opera_option.pop_object(2);
    ASSERT_TRUE(opera_option.size_object() == 8);
    opera_option.pop_object(15);
    ASSERT_TRUE(opera_option.size_object() == 8);
    for (int i = 1; i != 10; ++i) {
      /*OperaOption::Track track;
      track.batch_count = 1;
      OperaOption::Line line = {0x123, 21.34, 34.12, 34.12, 43.34};
      track.lines.push_back(line);
      track.types.push_back(OperaOption::LINE);
      track.id = i;
      track.ids.push_back(i);
      track.level_noise_track = 10;
      opera_option.push_back_track(track);*/
    }
}

TEST(OPERAOPTION, OPERATOR_OUT) {
  std::ostringstream strstream; 
  OperaOption opera_option;

  for (int i = 0; i != 10; ++i) {
    OperaOption::Radar radar;
    radar.id = i + 1;
    radar.type = OperaOption::R_STATIC;
    radar.start_x = 32.32;
    radar.start_y = 15.32;
    radar.radius_x = 98.321;
    radar.radius_y = 19.1342;
    radar.error_system = 1.321;
    radar.error_random = 3.31;
    radar.error_overall = 9.21341;
    radar.azimuth_range.push_back(std::make_pair(14.0, 50.0));

    opera_option.push_back_radar(radar);
  }

  for (int i=1; i!=5; ++i) {
    OperaOption::Track track;

    track.id = 100 + i;
    track.batch_count = 5;
    track.level_noise_track = 203;

    for (int j=0; j!=track.batch_count; ++j) {
      std::vector<float> accs;
      track.start_speeds.push_back(2.0);
      track.accelerations.push_back(accs);
      track.time_delays.push_back(14.4);
      track.ids.push_back(track.id * track.batch_count + j);
    }
    OperaOption::Line line;
    line.id = 143;
    line.start_x = 14.23;
    line.start_y = 27.53;
    line.end_x = 89.432;
    line.end_y = 15.8934;

    OperaOption::Circle circle;
    circle.id = 14312;
    circle.start_x = 14.431;
    circle.start_y = 19.431;
    circle.center_x = 98.431;
    circle.center_y = 32.412;
    circle.side_x = 41.234;
    circle.side_y = 14.874321;
    circle.angle_x = 98.13412;
    circle.angle_y = 29.412;

    track.types.push_back(OperaOption::LINE);
    track.lines.push_back(line);
    track.types.push_back(OperaOption::CIRCLE);
    track.circles.push_back(circle);

    std::size_t batch_count_size = static_cast<std::size_t>(track.batch_count);
    for (std::size_t j=0; j!=batch_count_size; ++j)
      for (std::size_t k=0; k!=track.types.size(); ++k)
        track.accelerations[j].push_back(5.0);
    opera_option.push_back_track(track);
  }

  strstream << opera_option;
  std::istringstream istrstream(strstream.str().c_str());

  OperaOption opera_option_temp;
  istrstream >> opera_option_temp;
  assert(opera_option == opera_option_temp);

  strstream.clear();
  std::stringstream mystrstream;
  mystrstream << opera_option_temp;
  assert(0 == strcmp(strstream.str().c_str(), mystrstream.str().c_str()));
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
