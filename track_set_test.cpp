#include "track_set.h"

#include <iostream>
#include <iomanip>

namespace tools{

class Test{
public:
  void RunAllTest(){
    TestFunctioin1();
  }

  void TestFunctioin1(){
    float interval = 1.0;
    float init_speed = 0.00026997840172;
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

    i = 0;
    Track2D::TrackUnitSet* track_unit_set1 = new Track2D::TrackUnitSet();
    track_unit_set1->push_back(new TrackUnit(line, acc_uniform, interval, init_speed));
    track_unit_set1->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(line, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(line, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(line, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(line, acc_constant, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    track_unit_set1->push_back(new TrackUnit(circle, acc_uniform, interval, (*track_unit_set1)[i++]->GetEndSpeed()));
    
    Track2D track0(track_unit_set, interval, init_speed);
    Track2D track1(track_unit_set, interval, init_speed);
    Track2D track2(track_unit_set, interval, init_speed);
    Track2D track3(track_unit_set, interval, init_speed);
    Track2D track4(track_unit_set, interval, init_speed);
    Track2D track5(track_unit_set, interval, init_speed);
    Track2D track6(track_unit_set1, interval, init_speed);

    std::vector<Track2D*> track_set;
    track_set.push_back(&track0);
    track_set.push_back(&track1);
    track_set.push_back(&track2);
    track_set.push_back(&track3);
    track_set.push_back(&track4);
    track_set.push_back(&track5);
    track_set.push_back(&track6);

    std::vector<Point2D*> init_points;
    init_points.push_back(new Point2D(0.0, 0.0));
    init_points.push_back(new Point2D(0.0, 0.0));
    init_points.push_back(new Point2D(0.0, 0.0));
    init_points.push_back(new Point2D(0.0, 0.0));
    init_points.push_back(new Point2D(0.0, 0.0));
    init_points.push_back(new Point2D(0.0, 0.0));
    init_points.push_back(new Point2D(0.0, 0.0));

    TrackSet2D track_set_2d(&track_set, &init_points, interval);

    TrackSet2D::Iterator iter(&track_set_2d);
    TrackSet2D::TrackSetState track_set_state;
    int count = 0;
    while(iter.Valid()){
      iter.Value(track_set_state);
      std::cout << std::setw(20) << "track no" 
      << std::setw(20) << "position"
      << std::setw(20) << "time"
      << std::setw(20) << "acc"
      << std::setw(20) << "speed"
      << std::setw(20) << "distance" << std::endl;
      for(std::size_t i = 0; i != track_set_state.track_set_state.size(); ++i)
        std::cout << std::setw(20) << i
        << std::setw(10) << track_set_state.track_set_state[i].point.x
        << std::setw(10) << track_set_state.track_set_state[i].point.y
        << std::setw(20) << track_set_state.track_set_state[i].tick 
        << std::setw(20) << track_set_state.track_set_state[i].acc 
        << std::setw(20) << track_set_state.track_set_state[i].speed
        << std::setw(20) << track_set_state.track_set_state[i].distance
        << std::endl;
      iter.Next();
      std::cout << std::endl;
      ++count;
    }
    std::cout << "sum tick: " << count << std::endl;
    std::cout << "sum tick:" << track_set_2d.GetSumTick() << std::endl;
    std::cout << "sum length:" << track_set_2d.GetSumLength() << std::endl;
  }
};

} //namespace tools

int main(){
  tools::Test().RunAllTest();
  return 0;
}
