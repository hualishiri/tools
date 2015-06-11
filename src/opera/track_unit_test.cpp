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
    while (iter.Valid()) {
      iter.Value(track_unit_state);
      iter.Next();
      ++count;
    }
    track_unit.GetEndPoint(track_unit_state.point);

    delete acc_variable;
    delete shape_circle;
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
