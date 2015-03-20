#include "opera/track_unit.h"

#include "opera/circle.h"
#include "opera/line.h"
#include "opera/acceleration.h"
#include "opera/shape.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

float MyFun(long time) {
  return sin(time);
}

class TRACKUNIT {};

TEST(TRACKUNIT, Iterator) {
    Acceleration* acc_variable = new VariableAcceleration(MyFun);
    Shape2D* shape_circle = new Circle2D(Point2D(40.176254, 40.176254),
                                         3.14156233);
    float interval = 1;
    float speed = 1; 
    TrackUnit track_unit(shape_circle, acc_variable, interval, speed);
    TrackUnit::Iterator iter(&track_unit);
    int count = 0;
    TrackUnit::TrackUnitState track_unit_state;
    LogDebug("\t%s\t%s\t%s\t%s\t%s\n",
             "position",
             "time",
             "acc",
             "speed",
             "distance");
    while (iter.Valid()) {
      iter.Value(track_unit_state);
      LogDebug("\t%f\t%f\t%d\t%f\t%f\t%f\n",
               track_unit_state.point.x,
               track_unit_state.point.y,
               track_unit_state.tick,
               track_unit_state.acc,
               track_unit_state.speed,
               track_unit_state.distance);
      iter.Next();
      ++count;
    }
    
    track_unit.GetEndPoint(track_unit_state.point);
    LogDebug("Track Unit End Position: (%f, %f)\n",
             track_unit_state.point.x,
             track_unit_state.point.y);
    LogDebug("Track Unit Sum Step: %d\n", count);
    LogDebug("Track Unit Sum Length: %f\n", track_unit.GetSumLength());
    LogDebug("Track Unit End Speed: %f\n", track_unit.GetEndSpeed());
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
