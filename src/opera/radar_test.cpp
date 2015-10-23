#include "opera/radar.h"

#include <sstream>
#include <fstream>

#include "util/testharness.h"
#include "util/tool.h"

namespace tools {

class RADAR2D {};

TEST(RADAR2D, RadarErrorOperator) {
  Radar2D::RadarError radar_error_lhs = {
    10.03143,
    9.9819,
    10.03143,
    9.9819,
    10.03143,
    10.03143,
    10.03143,
    9.9819,
    9.9819,
    9.9819,
    10.03143,
    9.9819
  };
  Radar2D::RadarError radar_error_rhs = {
    10.03143,
    9.9819,
    10.03143,
    9.9819,
    10.03143,
    10.03143,
    10.03143,
    9.9819,
    9.9819,
    9.9819,
    10.03143,
    9.9819
  };
  ASSERT_TRUE(radar_error_lhs == radar_error_rhs);
  radar_error_rhs.error_random_distance = 3.54;
  ASSERT_TRUE(!(radar_error_lhs == radar_error_rhs));
  std::stringstream out;
  out << radar_error_lhs;
  std::stringstream in(out.str().c_str());
  Radar2D::RadarError radar_error_input;
  in >> radar_error_input;
  ASSERT_TRUE(radar_error_lhs == radar_error_input);
}

TEST(RADAR2D, RadarStateOperator) {
  Radar2D::RadarState lhs, rhs;
  lhs.id = 0x7843917421;
  lhs.type = 3;
  lhs.point.x = 34.431;
  lhs.point.y = 27.3131;
  std::size_t length = 10;
  Radar2D::RadarError radar_error_lhs = {
    10.03143,
    9.9819,
    10.03143,
    9.9819,
    10.03143,
    10.03143,
    10.03143,
    9.9819,
    9.9819,
    9.9819,
    10.03143,
    9.9819
  };
  for (std::size_t i=0; i!=length; ++i) {
    lhs.ids.push_back(static_cast<long long>(i*i));
    lhs.targets.push_back(Point2D(i/1.0/(i+1), i/1.0/(i+1)));
    lhs.targets_height.push_back(i*i/1.0/(i+2));
    lhs.targets_angle_azimuth.push_back(i*i/1.0/(i+2));
    lhs.targets_real_distance.push_back(i*i/1.0/(i+2));
    lhs.targets_real_elevation.push_back(i*i/1.0/(i+2));
    lhs.targets_real_velocity.push_back(i*i/1.0/(i+2));
    lhs.targets_radar.push_back(Point2D(i/1.0/(i+1), i/1.0/(i+1)));
    lhs.targets_radar_height.push_back(i*i/1.0/(i+2));
    lhs.targets_detected_azimuth.push_back(i*i/1.0/(i+2));
    lhs.targets_detected_distance.push_back(i*i/1.0/(i+2));
    lhs.targets_detected_elevation.push_back(i*i/1.0/(i+2));
    lhs.targets_detected_velocity.push_back(i*i/1.0/(i+2));
    lhs.targets_filter.push_back(Point2D(i/1.0/(i+1), i/1.0/(i+1)));
    lhs.targets_error.push_back(radar_error_lhs);
  }

  rhs.id = 0x7843917421;
  rhs.type = 3;
  rhs.point.x = 34.431;
  rhs.point.y = 27.3131;
  Radar2D::RadarError radar_error_rhs = {
    10.03143,
    9.9819,
    10.03143,
    9.9819,
    10.03143,
    10.03143,
    10.03143,
    9.9819,
    9.9819,
    9.9819,
    10.03143,
    9.981932
  };
  for (std::size_t i=0; i!=length; ++i) {
    rhs.ids.push_back(static_cast<long long>(i*i));
    rhs.targets.push_back(Point2D(i/1.0/(i+1), i/1.0/(i+1)));
    rhs.targets_height.push_back(i*i/1.0/(i+2));
    rhs.targets_angle_azimuth.push_back(i*i/1.0/(i+2));
    rhs.targets_real_distance.push_back(i*i/1.0/(i+2));
    rhs.targets_real_elevation.push_back(i*i/1.0/(i+2));
    rhs.targets_real_velocity.push_back(i*i/1.0/(i+2));
    rhs.targets_radar.push_back(Point2D(i/1.0/(i+1), i/1.0/(i+1)));
    rhs.targets_radar_height.push_back(i*i/1.0/(i+2));
    rhs.targets_detected_azimuth.push_back(i*i/1.0/(i+2));
    rhs.targets_detected_distance.push_back(i*i/1.0/(i+2));
    rhs.targets_detected_elevation.push_back(i*i/1.0/(i+2));
    rhs.targets_detected_velocity.push_back(i*i/1.0/(i+2));
    rhs.targets_filter.push_back(Point2D(i/1.0/(i+1), i/1.0/(i+1)));
    rhs.targets_error.push_back(radar_error_rhs);
  }
  
  ASSERT_TRUE(!(lhs == rhs));
  std::stringstream out;
  out << lhs;
  std::string str_out = out.str();
  std::stringstream in(out.str().c_str());
  std::string str_in = in.str();
  Radar2D::RadarState radar_state_result;
  in >> radar_state_result;
  ASSERT_TRUE(lhs == radar_state_result);

  std::stringstream stream_bin;
  WriteToFile(stream_bin, lhs);

  std::ofstream ofstream_bin("test.dat", std::ios::binary);
  ofstream_bin << stream_bin.rdbuf();
  ofstream_bin.close();

  std::ifstream ifstream_bin("test.dat", std::ios::binary);
  stream_bin.str("");
  stream_bin << ifstream_bin.rdbuf();
  stream_bin.seekg(0, stream_bin.beg);

  Radar2D::RadarState temp_bin;
  ReadFromFile(stream_bin, temp_bin);
  ASSERT_TRUE(temp_bin == lhs);
}

}

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
