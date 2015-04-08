#include "opera_random.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "opera/circle.h"
#include "util/tool.h"
#include "util/logger.h"

namespace tools {

void OperaRandom::GetResult(RandomOpera &random_opera) const {
  int radar_number = GetRadarNumber(313);
  int track_number = GetTrackNumber(436);
  assert(radar_number >= 0);
  assert(track_number >= 0);
  for (int i=0; i!=radar_number; ++i) {
    random_opera.radars.push_back(GetRadar(12*i*i + 4));
  }
  for (int i=0; i!=track_number; ++i) {
    random_opera.tracks.push_back(GetTrack(3*i+8*i));
  }
}

int OperaRandom::GetRadarNumber(int seed) const {
  double radar_number = GetNumber(
      static_cast<double>(opera_random_para_.radar_number_min),
      static_cast<double>(opera_random_para_.radar_number_max),
      seed);
  return static_cast<int>(radar_number);
}

int OperaRandom::GetTrackNumber(int seed) const {
  double track_number = GetNumber(
      static_cast<double>(opera_random_para_.track_number_min),
      static_cast<double>(opera_random_para_.track_number_max),
      seed);
  return static_cast<int>(track_number);
}

OperaRandom::Radar OperaRandom::GetRadar(int seed) const {
  Radar radar;
  GetRandomPosition(radar.center_x, radar.center_y, seed); 
  radar.radius = GetNumber(opera_random_para_.radar_radius_min,
                           opera_random_para_.radar_radius_max,
                           seed + 1);
  return radar;
}

OperaRandom::Track OperaRandom::GetTrack(int seed) const {
  int track_unit_number = static_cast<int>(
      GetNumber(opera_random_para_.track_unit_number_min,
                opera_random_para_.track_unit_number_max,
                seed));
  int track_line_number = static_cast<int>(GetNumber(1,
                                                     track_unit_number,
                                                     seed + 1));
  int track_circle_number = track_unit_number - track_line_number;
  Track track;
  std::stack<std::pair<double, double> > position;
  std::stack<int> position_order;
  std::stack<double> angles;
  GetRandomPositionSet(position, track_unit_number + 1, (seed << 2) + 1);
  GetRandomPositionOrder(position_order,
                         track_unit_number,
                         track_line_number,
                         (seed << 2) + 2);
  GetRandomAngle(angles, track_circle_number, (seed << 2) + 3);

  std::stack<std::pair<double ,double> > position_temp(position);
  std::stack<double> angle_temp(angles);
  std::stack<int> position_order_temp(position_order);

  while(!position_order_temp.empty()) {
    position_order_temp.pop();
  }
  while (!position_temp.empty()) {
    position_temp.pop();
  }
  while (!angle_temp.empty()) {
    angle_temp.pop();
  }

  assert(track_unit_number + 1 == static_cast<int>(position.size()));
  assert(track_unit_number == static_cast<int>(position_order.size()));
  assert(static_cast<int>(angles.size()) == track_circle_number);
  
  double last_x = 0.0;
  double last_y = 0.0;

  if (0 == position_order.top()) {
    Line line;
    line.start_x = position.top().first;
    line.start_y = position.top().second;
    position.pop();
    line.end_x = position.top().first;
    line.end_y = position.top().second;
    position.pop();
    last_x = line.end_x;
    last_y = line.end_y;
    track.lines.push_back(line);
    track.types.push_back(LINE);
  } else {
    Circle circle;
    circle.start_x = position.top().first;
    circle.start_y = position.top().second;
    position.pop();
    circle.center_x = position.top().first;
    circle.center_y = position.top().second;
    position.pop();
    circle.angle = angles.top();
    angles.pop();
    GetArcEndPoint(circle, last_x, last_y);
    track.circles.push_back(circle);
    track.types.push_back(CIRCLE);
  }
  position_order.pop();
  while (!position_order.empty()) {
    if (0 == position_order.top()) {
      assert(!position.empty());
      assert(!position_order.empty());
      Line line;
      line.start_x = last_x;
      line.start_y = last_y;
      line.end_x = position.top().first;
      line.end_y = position.top().second;
      position.pop();
      last_x = line.end_x;
      last_y = line.end_y;
      track.lines.push_back(line);
      track.types.push_back(LINE);
    } else {
      assert(!position.empty());
      assert(!position_order.empty());
      assert(!angles.empty());
      Circle circle;
      circle.start_x = last_x;
      circle.start_y = last_y;
      circle.center_x = position.top().first;
      circle.center_y = position.top().second;
      position.pop();
      circle.angle = angles.top();
      angles.pop();
      GetArcEndPoint(circle, last_x, last_y);
      track.circles.push_back(circle);
      track.types.push_back(CIRCLE);
    }
    position_order.pop();
  }
  return track;
}

bool OperaRandom::ParameterValid() const {
  if (RangeValid(opera_random_para_.radar_number_min,
                 opera_random_para_.radar_number_max)
      && RangeValid(opera_random_para_.track_number_min,
                    opera_random_para_.track_number_max)
      && RangeValid(opera_random_para_.track_unit_number_min,
                    opera_random_para_.track_unit_number_max)
      && RangeValid(opera_random_para_.radar_radius_min,
                    opera_random_para_.radar_radius_max))
    return true;
  return false;
}

bool OperaRandom::RangeValid(int min, int max) const {
  if (min > 0 && max > 0 && max >= min)
    return true;
  return false;
}

bool OperaRandom::RangeValid(double min, double max) const {
  if (min > 0.0 && max > 0.0 && max >= min)
    return true;
  return false;
}

double OperaRandom::GetNumber(double min, double max, int seed) const {
  return min + (max - min ) * fabs(GetRandNumber(seed));
}

void OperaRandom::GetRandomPosition(double &x, double &y, int seed) const {
  x = GetNumber(opera_random_para_.rectangle_up_x,
                opera_random_para_.rectangle_down_x,
                seed);
  y = GetNumber(opera_random_para_.rectangle_up_y,
                opera_random_para_.rectangle_down_y,
                seed << 2);
}

void OperaRandom::GetArcEndPoint(const Circle& circle,
                                 double &x,
                                 double &y) const {
  Point2D point(circle.center_x - circle.start_x,
                circle.center_y - circle.start_y);
  Circle2D circle_internal(point, circle.angle); 
  Point2D point_result;
  circle_internal.GetPoint(circle_internal.GetLength(), point_result);
  x = point_result.x + circle.start_x;
  y = point_result.y + circle.start_y;
}

void OperaRandom::GetRandomPositionSet(
    std::stack<std::pair<double, double> > &position,
    int n,
    int seed) const {
  while(!position.empty())
    position.pop();
  double x, y;
  x = y = 0;
  for (int i=0; i!=n; ++i) {
    GetRandomPosition(x, y, seed + i * i + 1);
    position.push(std::make_pair(x, y));
  }
}

void OperaRandom::GetRandomPositionOrder(std::stack<int> &pos_order,  
                                         int track_unit_number,
                                         int line_number,
                                         int seed) const {
  while(!pos_order.empty())
    pos_order.pop();
  int *array = new int[track_unit_number];
  for (int i=0; i!=line_number; ++i)
    array[i] = 0;
  for (int i=line_number; i!=track_unit_number; ++i)
    array[i] = 1;
  for (int i=0; i!=track_unit_number; ++i) {
    srand(time(0) + i);
    int index = rand() % (track_unit_number - i);
    int temp = array[index];
    array[index] = array[track_unit_number-1-i];
    array[track_unit_number-1-i] = temp;
    pos_order.push(array[track_unit_number-1-i]);
  }
}

void OperaRandom::GetRandomAngle(std::stack<double> &angles,
                                 int n,
                                 int seed) const {
  double x = 0.0;
  int i = 0;
  while (static_cast<int>(angles.size()) != n) {
    x = GetNumber(-2.0 * T_PI, 2.0 * T_PI, 2 * seed + seed * seed + i);
    if ( x > T_PI / 6.0 || x < T_PI / (-6.0) )
      angles.push(x);
    ++i;
  }
}

} //namespace tools
