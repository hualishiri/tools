#include "track_unit.h"

#include <assert.h>
#include <math.h>

#include <iomanip>
#include <iostream>
#include <vector>

#include "shape.h"

namespace tools {
  
float MyFun(unsigned long time) {
  return sin(time);
}

class Test {
 public:
  int RunAllTest() {
    TestFunctionTrackUnitGetSumTick();
    return 0;
  }

  void TestFunctionTrackUnitGetSumTick() {
    Acceleration* acc_uniform = new UniformAcceleration();
    Acceleration* acc_constant = new ConstantAcceleration(0.1);
    Acceleration* acc_variable = new VariableAcceleration(MyFun);
    Shape2D* shape = new Line2D(Point2D(40, 40));
    Shape2D* shape_circle = new Circle2D(Point2D(40.176254, 40.176254),
                                         3.14156233);
    float interval = 1;
    float speed = 1; 
    TrackUnit track_unit(shape_circle, acc_variable, interval, speed);
    TrackUnit::Iterator iter(&track_unit);
    int count = 0;
    TrackUnit::TrackUnitState track_unit_state;
    std::cout << std::setw(20) << "position" 
      << std::setw(20) << "time"
      << std::setw(20) << "acc"
      << std::setw(20) << "speed"
      << std::setw(20) << "distance" << std::endl;
    while (iter.Valid()) {
      iter.Value(track_unit_state);
      std::cout << std::setw(10) << track_unit_state.point.x
          << std::setw(10) << track_unit_state.point.y
          << std::setw(20) << track_unit_state.tick
          << std::setw(20) << track_unit_state.acc
          << std::setw(20) << track_unit_state.speed
          << std::setw(20) << track_unit_state.distance << std::endl;
      iter.Next();
      ++count;
    }
    
    track_unit.GetEndPoint(track_unit_state.point);
    std::cout << "[" << track_unit_state.point.x  << "," 
        << track_unit_state.point.y << "]" << std::endl;
    std::cout << std::endl << count <<std::endl;
    std::cout << std::endl << "track sum length: " 
        << track_unit.GetSumLength() <<std::endl;
    std::cout << std::endl << "track end speed: " 
        << track_unit.GetEndSpeed()<<std::endl;
    }
};

} //namespace tools

int main(int argc, char** argv) {
  return tools::Test().RunAllTest();
}
