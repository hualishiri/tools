#include "opera/opera_random.h"

#include "util/testharness.h"
#include "util/logger.h"
#include "util/tool.h"

namespace tools {

bool IsInRectangle(const OperaRandom::OperaRandomParameter& opera_para,
    double &x, double &y);

class OPERARANDOM{};

TEST(OPERARANDOM, GetRadar) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    5, 10,
    3.0, 10.0,
    3, 5,
    5, 10
  };
  for (int i=0; i!=1000; ++i) {
    OperaRandom opera_random(opera_random_parameter);
    OperaRandom::Radar radar = opera_random.GetRadar(10);
    bool is_right = (radar.center_x <= opera_random_parameter.rectangle_up_x
        && radar.center_x >= opera_random_parameter.rectangle_down_x)
        || (radar.center_x <= opera_random_parameter.rectangle_down_x
        && radar.center_x >= opera_random_parameter.rectangle_up_x);
    ASSERT_TRUE(is_right);
    is_right = (radar.center_y <= opera_random_parameter.rectangle_up_y
        && radar.center_y >= opera_random_parameter.rectangle_down_y)
        || (radar.center_y <= opera_random_parameter.rectangle_down_y
        && radar.center_y >= opera_random_parameter.rectangle_up_y);
    ASSERT_TRUE(is_right);
    ASSERT_GE(radar.radius, opera_random_parameter.radar_radius_min);
    ASSERT_LE(radar.radius, opera_random_parameter.radar_radius_max);
  }
}

TEST(OPERARANDOM, GetRadarNumber) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  OperaRandom opera_random(opera_random_parameter);
  for (int i=0; i!=1000; ++i) {
    int radar_number = opera_random.GetRadarNumber(i);
    ASSERT_GE(radar_number, opera_random_parameter.radar_number_min);
    ASSERT_LE(radar_number, opera_random_parameter.radar_number_max);
  }
}

TEST(OPERARANDOM, GetTrackNumber) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  OperaRandom opera_random(opera_random_parameter);
  for (int i=0; i!=1000; ++i) {
    int track_number = opera_random.GetTrackNumber(i);
    ASSERT_GE(track_number, opera_random_parameter.track_number_min);
    ASSERT_LE(track_number, opera_random_parameter.track_number_max);
  }
}

TEST(OPERARANDOM, GetRandomPositionSet) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  std::stack<std::pair<double, double> > position_set;
  OperaRandom opera_random(opera_random_parameter);

  for (int i=10; i!=20; ++i) {
    opera_random.GetRandomPositionSet(position_set, i, i);
    ASSERT_EQ(static_cast<int>(position_set.size()), i);
    while (!position_set.empty()) {
      bool is_right = IsInRectangle(opera_random_parameter,
                                    position_set.top().first,
                                    position_set.top().second);   
      position_set.pop();
      ASSERT_TRUE(is_right);
    }
  }
}

TEST(OPERARANDOM, GetRandomPositionOrder) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  std::stack<int> position_order;
  OperaRandom opera_random(opera_random_parameter);

  for (int i=10; i!=20; ++i) {
    opera_random.GetRandomPositionOrder(position_order, i, i/2, i);
    ASSERT_EQ(static_cast<int>(position_order.size()), i);

    while (!position_order.empty()) {
      LogDebug("%d", position_order.top());
      position_order.pop();
    }
    LogDebug("\n");
  }
}

TEST(OPERARANDOM, GetRandomAngle) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  std::stack<double> angles;
  OperaRandom opera_random(opera_random_parameter);

  for (int i=10; i!=20; ++i) {
    opera_random.GetRandomAngle(angles, i, i);
    ASSERT_EQ(static_cast<int>(angles.size()), i);

    while (!angles.empty()) {
      ASSERT_GE(angles.top(), -2.0 * T_PI);
      ASSERT_LE(angles.top(), 2.0 * T_PI);
      angles.pop();
    }
    LogDebug("\n");
  }
}

TEST(OPERARANDOM, GetTrack) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  std::stack<double> angles;
  OperaRandom opera_random(opera_random_parameter);
  OperaRandom::Track track = opera_random.GetTrack(100);

  int line_index = 0;
  int circle_index = 0;
  for (int i=0; i!=static_cast<int>(track.types.size()); ++i) {

    if (track.types[i] == OperaRandom::LINE)
      LogInfo("Line: (%f, %f), (%f, %f)",
              track.lines[line_index].start_x,
              track.lines[line_index].start_y,
              track.lines[line_index].end_x,
              track.lines[line_index].end_y);
    ++line_index;
  if (OperaRandom::CIRCLE == track.types[i])
    LogInfo("Circle: (%f, %f), (%f, %f), %f",
            track.circles[circle_index].start_x,
            track.circles[circle_index].start_y,
            track.circles[circle_index].center_x,
            track.circles[circle_index].center_y,
            track.circles[circle_index].angle
            );
    ++circle_index;
  }
}

/*TEST(OPERARANDOM, GetResult) {
  OperaRandom::OperaRandomParameter opera_random_parameter = {
    10.0, 10.0,
    120.0, 120.0,
    3, 10,  //radar number range
    3.0, 10.0,  //radar radius range
    3, 5, //track number range
    5, 10  // track unit number range
  };
  std::stack<double> angles;
  OperaRandom opera_random(opera_random_parameter);

  LogInfo("Result first");
  OperaRandom::RandomOpera random_opera;
  opera_random.GetResult(random_opera);
  std::vector<OperaRandom::Radar> radars = random_opera.radars;
  std::vector<OperaRandom::Track> tracks = random_opera.tracks;

  ASSERT_LE(static_cast<int>(radars.size()),
            opera_random_parameter.radar_number_max);
  ASSERT_GE(static_cast<int>(radars.size()),
            opera_random_parameter.radar_number_min);
  ASSERT_LE(static_cast<int>(tracks.size()),
            opera_random_parameter.track_number_max);
  ASSERT_GE(static_cast<int>(tracks.size()),
            opera_random_parameter.track_number_min);
}*/

bool IsInRectangle(const OperaRandom::OperaRandomParameter& opera_para,
    double &x, double &y) {
  bool is_right = false;
  is_right = ((x >= opera_para.rectangle_up_x 
      && x <= opera_para.rectangle_down_x)
      || (x >= opera_para.rectangle_down_x
      && x <= opera_para.rectangle_up_x))
      && ((y >= opera_para.rectangle_up_y
      && y <= opera_para.rectangle_down_y) 
      || (y >= opera_para.rectangle_down_y
      && y <= opera_para.rectangle_up_y));
  return is_right;
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
