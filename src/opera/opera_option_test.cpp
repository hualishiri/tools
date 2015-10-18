#include "opera/opera_option.h"

#include <string.h>

#include <sstream>
#include <iostream>

#include "util/testharness.h"
#include "util/tool.h"

namespace tools {

class OPERAOPTION {};

TEST(OPERAOPTION, Radar) {
  OperaOption::Radar radar;
  radar.set_type(OperaOption::R_STATIC);
  assert(radar.get_type() == OperaOption::R_STATIC);
  
  radar.set_type(OperaOption::R_DYNAMIC);
  assert(radar.get_type() == OperaOption::R_DYNAMIC);

  radar.set_type_trival(0x00);
  assert(radar.get_type_trival() == 0x00);

  radar.set_type_trival(0x01);
  assert(radar.get_type_trival() == 0x01);
}

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
      radar.height = 1432.4314312;

      radar.error.error_random_azimuth = 0.001;
      radar.error.error_random_distance = 1.0;
      radar.error.error_random_elevation = 0.001;
      radar.error.error_system_azimuth = 0.001;
      radar.error.error_system_distance = 1.0;
      radar.error.error_system_elevation = 0.001;

      radar.detecting_objects_types = 
          OperaOption::AIRCRAFT | OperaOption::LANDCRAFT;
      radar.azimuth_range.push_back(std::make_pair(14.0, 50.0));
      opera_option.push_back_radar(radar);
    }
    opera_option.pop_radar(2);
    ASSERT_TRUE(opera_option.size_radar() == 8);
    opera_option.pop_radar(15);
    ASSERT_TRUE(opera_option.size_radar() == 8);

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
    radar.height = 23.4312431;
    radar.error.error_random_azimuth = 0.01;
    radar.error.error_random_distance = 1.0;
    radar.error.error_random_distance = 0.01;
    radar.error.error_system_azimuth = 0.01;
    radar.error.error_system_distance = 1.0;
    radar.error.error_system_elevation = 0.01;

    radar.detecting_objects_types = OperaOption::AIRCRAFT | 
        OperaOption::LANDCRAFT;
    radar.azimuth_range.push_back(std::make_pair(14.0, 50.0));

    opera_option.push_back_radar(radar);
  }

  for (int i=1; i!=5; ++i) {
    OperaOption::Track track;

    track.id = 100 + i;
    track.batch_count = 5;
    track.level_noise_track = 203;

    for (int j=0; j!=track.batch_count; ++j) {
      std::vector<double> accs;
      track.start_speeds.push_back(2.0);
      track.accelerations.push_back(accs);
      track.time_delays.push_back(14.4);
      track.ids.push_back(track.id * track.batch_count + j);
      track.track_types.push_back(OperaOption::AIRCRAFT | OperaOption::LANDCRAFT);
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
    circle.angle = 1.78;

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

  std::stringstream strstream_bin;
  ASSERT_TRUE(opera_option == opera_option_temp);

  std::stringstream stream_bin;
  WriteToFile(stream_bin, opera_option);
  stream_bin.seekg(0, stream_bin.beg);
  OperaOption temp_bin;
  ReadFromFile(stream_bin, temp_bin);
  ASSERT_TRUE(temp_bin == opera_option);
  //assert(0 == strcmp(strstream.str().c_str(), mystrstream.str().c_str()));

}

TEST(OPERAOPTION, Reserve) {
  OperaOption::Reserve reserve;
  reserve.set_int(1, 3);
  ASSERT_TRUE(3 == reserve.get_int(1)); 

  reserve.set_int(1, 4);
  ASSERT_TRUE(4 == reserve.get_int(1)); 

  reserve.set_double(2, 3.5);
  ASSERT_TRUE(DoubleEqual(3.5, reserve.get_double(2)));

  reserve.set_double(2, 3.7);
  ASSERT_TRUE(DoubleEqual(3.7, reserve.get_double(2)));

  reserve.set_string(3, "caobingzhang");
  ASSERT_TRUE("caobingzhang" == reserve.get_string(3));

  reserve.set_string(3, "zhanghuali");
  ASSERT_TRUE("zhanghuali" == reserve.get_string(3));

  std::stringstream in, out;
  out << reserve;
  in.str(out.str());
  OperaOption::Reserve temp;
  in >> temp;
  ASSERT_TRUE(temp == reserve);
}

TEST(OPERAOPTION, Error) {
  OperaOption::Error error = {
    43.34124312,
    12.431512,
    923.0431243,
    12.7348794,
    92.4317879,
    431.431243
  };

  OperaOption::Error temp;
  std::stringstream in, out;
  out << error;
  in.str(out.str());
  in >> temp;
  ASSERT_TRUE(temp == error);
}

TEST(OPERAOPTION, RadarOperator) {
  OperaOption::Radar radar;
  radar.id = 15;
  radar.type = 17;
  radar.detecting_objects_types = 2;
  radar.track_id = 17;
  radar.start_x = 14.031;
  radar.start_y = 13.031;
  radar.radius_x = 98.4312;
  radar.radius_y = 88.4312;
  radar.height = 98.3412123;

  OperaOption::Error error = {
    43.34124312,
    12.431512,
    923.0431243,
    12.7348794,
    92.4317879,
    431.431243
  };

  radar.error = error;

  radar.azimuth_range.push_back(std::make_pair(14.43143, 89.4312));
  radar.azimuth_range.push_back(std::make_pair(14.43143, 89.4312));
  radar.azimuth_range.push_back(std::make_pair(14.43143, 89.4312));

  OperaOption::Reserve reserve;
  reserve.set_int(1, 34);
  reserve.set_int(2, 38);
  reserve.set_int(3, 38);
  reserve.set_double(4, 89.4312);
  reserve.set_double(5, 819.4312);
  reserve.set_double(6, 43189.4312);
  reserve.set_string(7, "woshishenme");
  reserve.set_string(8, "nishishenmea");

  radar.data = reserve;

  OperaOption::Radar temp;
  std::stringstream in, out;
  out << radar;
  in.str(out.str());
  in >> temp;
  ASSERT_TRUE(temp == radar);

  std::stringstream stream_bin;
  WriteToFile(stream_bin, radar);
  stream_bin.seekg(0, stream_bin.beg);
  OperaOption::Radar temp_bin;
  ReadFromFile(stream_bin, temp_bin);
  ASSERT_TRUE(temp_bin == radar);
}

TEST(OPERAOPTION, Shape) {
  OperaOption::Line line = {
    32,
    12.43124,
    13.123412,
    98.431243,
    62.43124312
  };

  OperaOption::Circle circle = {
    892,
    13.431412,
    19.78349712,
    72.43134,
    95.12521,
    18.12521
  };

  OperaOption::Line temp_line;
  std::stringstream in, out;
  out << line;
  in.str(out.str());
  in >> temp_line;
  ASSERT_TRUE(temp_line == line);

  OperaOption::Circle temp_circle;
  std::stringstream in_c, out_c;
  out_c << circle;
  in_c.str(out_c.str());
  in_c >> temp_circle;
  ASSERT_TRUE(temp_circle == circle);
}

TEST(OPERAOPTION, TrackOperator) {
  OperaOption::Track track;
  track.id = 431289;
  track.reserve.type = 2;

  track.start_speeds.push_back(432.4321);
  track.start_speeds.push_back(8332.4318);
  track.start_speeds.push_back(6721.4321);
  track.start_speeds.push_back(432.8419);

  std::vector<double> temp;
  temp.push_back(432.4314);
  temp.push_back(4287.4314);
  temp.push_back(4371289.4314);
  temp.push_back(432.4719);

  track.accelerations.push_back(temp);
  track.accelerations.push_back(temp);
  track.accelerations.push_back(temp);
  track.accelerations.push_back(temp);

  track.time_delays.push_back(432.4321);
  track.time_delays.push_back(8332.4318);
  track.time_delays.push_back(6721.4321);
  track.time_delays.push_back(432.8419);

  track.batch_count = 15;
  track.level_noise_track = 234.43124232;

  track.ids.push_back(1414198);
  track.ids.push_back(1481791);
  track.ids.push_back(5671943);
  track.ids.push_back(927582);
  
  OperaOption::Line line = {
    4321,
    4231879.431,
    239.34123,
    58.63456,
    634.634653
  };

  OperaOption::Circle circle = {
    4321,
    4231879.431,
    239.34123,
    58.63456,
    1432.63456,
    634.634653
  };

  track.lines.push_back(line);
  track.lines.push_back(line);
  track.lines.push_back(line);

  track.circles.push_back(circle);
  track.circles.push_back(circle);
  track.circles.push_back(circle);
  track.circles.push_back(circle);
  track.circles.push_back(circle);
  track.circles.push_back(circle);

  track.types.push_back(OperaOption::LINE);
  track.types.push_back(OperaOption::LINE);
  track.types.push_back(OperaOption::LINE);
  track.types.push_back(OperaOption::LINE);

  std::stringstream strstream;
  strstream << track;
  OperaOption::Track temp_track;
  strstream >> temp_track;
  ASSERT_TRUE(track == temp_track);

  std::stringstream stream_bin;
  WriteToFile(stream_bin, track);
  stream_bin.seekg(0, stream_bin.beg);
  OperaOption::Track temp_bin;
  ReadFromFile(stream_bin, temp_bin);
  ASSERT_TRUE(temp_bin == track);
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
