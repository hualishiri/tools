#include "track.h"

#include <iostream>
#include <iomanip>
#include "track_unit.h"
#include "shape.h"

namespace tools{

class Test{
public:
  void RunAllTest(){
    FunctionTest1();   
  }

  void FunctionTest1(){
    float interval = 1.0*0.1;
    float init_speed = 0.00026997840172*10000;
    int i=0;
    Shape2D* line = new Line2D(Point2D(0.789872, 0.721040));
    Shape2D* circle = new Circle2D(Point2D(0.789872, 0.721040), 3.1415);
    Acceleration* acc_uniform = new UniformAcceleration();
    Acceleration* acc_constant = new ConstantAcceleration(0.00001);
    Track2D::TrackUnitSet* track_unit_set = new Track2D::TrackUnitSet();
    track_unit_set->push_back(new TrackUnit(line, acc_uniform, interval, init_speed));
    track_unit_set->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(line, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(line, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(line, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    track_unit_set->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set)[i++]->GetEndSpeed()));
    
    Track2D track(track_unit_set, interval, init_speed);
    Track2D::Iterator iter(&track);
    Track2D::TrackState track_state;
    std::cout << std::setw(20) << "position" 
    << std::setw(20) << "time"
    << std::setw(20) << "acc"
    << std::setw(20) << "speed"
    << std::setw(20) << "distance" << std::endl;
    while(iter.Valid()){
      iter.Value(track_state);
      std::cout << std::setw(10) << track_state.point.x
      << std::setw(10) << track_state.point.y
      << std::setw(20) << track_state.tick
      << std::setw(20) << track_state.acc
      << std::setw(20) << track_state.speed
      << std::setw(20) << track_state.distance << std::endl;       
      iter.Next();
    }
    /*
    iter.Reset();
    while(iter.Valid()){
      iter.Value(track_state);
      std::cout << std::setw(10) << track_state.point.x
      << std::setw(10) << track_state.point.y
      << std::setw(20) << track_state.tick
      << std::setw(20) << track_state.acc
      << std::setw(20) << track_state.speed
      << std::setw(20) << track_state.distance << std::endl;       
      iter.Next();
    }*/


    std::cout << "Length: " << track.GetLength() << std::endl;
    std::cout << "SumTick: " << track.GetSumTick() << std::endl;
  }
};

} //namespace tools

int main(){
  tools::Test().RunAllTest();
  return 0;
}
