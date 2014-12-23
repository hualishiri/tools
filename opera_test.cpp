#include "opera.h"

#include <iostream>
#include <iomanip>

namespace tools{
namespace test{
class Test{
public:
  void RunAllTest(){
    FunctionTest();
  }
  void FunctionTest(){
    double location[] = {
      1.0, 1.0,
      4.0, 4.0
    };
    double init_speed[] = {
      0.0001,
      0.002
    };
    int len = sizeof(location)/sizeof(double)/2;
    float interval = 1.0f;
    Acceleration* acc_uniform = new UniformAcceleration();
    Acceleration* acc_constant = new ConstantAcceleration(0.0000001);
    TrackSet2D::TrackSet track_set_rep;
    for(int i=0; i!=len; ++i){
      for(int j=0; j!=len; ++j){
        if(i == j) continue;
        Shape2D* line1 = new Line2D(Point2D(location[i*2], location[i*2+1]));
        Shape2D* line2 = new Line2D(Point2D(location[j*2], location[j*2+1]));
        TrackUnit* track_unit1 = new TrackUnit(line1, acc_uniform, interval, init_speed[i]);
        TrackUnit* track_unit2 = new TrackUnit(line2, acc_constant, interval, track_unit1->GetEndSpeed());
        Track2D::TrackUnitSet* track_unit_set = new Track2D::TrackUnitSet();
        track_unit_set->push_back(track_unit1);
        track_unit_set->push_back(track_unit2);
        Track2D* track = new Track2D(track_unit_set, interval, init_speed[i]);
        track_set_rep.push_back(track);
      }
    }
    TrackSet2D::TrackSetPosition track_set_position;
    for(int i = 0; i != len; ++i){
      track_set_position.push_back(new Point2D(location[2*i], location[2*i+1]));
    }
    TrackSet2D track_set(&track_set_rep, &track_set_position, interval);
    //init finished
    //
    //
    RadarSet2D::RadarSet rep_radar_set;
    for(int i=0; i!=len; ++i){
      rep_radar_set.push_back(new MechanicalRadar2D(location[2*i], location[2*i+1], 3));
    }
    RadarSet2D* radar_set = new RadarSet2D(&rep_radar_set); 

    Opera2D* opera = new Opera2D(&track_set, radar_set);

    Opera2D::Iterator iter(opera);
    Opera2D::OperaState opera_state;
    long long tick_cur = 1;
    while(iter.Valid()){
      std::cout << "==============================================="<< std::endl;
      //一次时间迭代
      iter.Value(opera_state);
      std::cout << std::setw(20) << "tick_no" 
      << std::setw(20) << "track_no"
      << std::setw(20) << "position"
      << std::setw(20) << "time"
      << std::setw(20) << "acc"
      << std::setw(20) << "speed"
      << std::setw(20) << "distance" << std::endl;
        for(std::size_t j = 0; j != opera_state.track_set_state.track_set_state.size(); ++j)
          std::cout << std::setw(20) << tick_cur
          << std::setw(20) << j << " "
          << std::setprecision(6) << opera_state.track_set_state.track_set_state[j].point.x << ","
          << std::setprecision(6) << opera_state.track_set_state.track_set_state[j].point.y
          << std::setw(20) << opera_state.track_set_state.track_set_state[j].tick 
          << std::setw(20) << opera_state.track_set_state.track_set_state[j].acc 
          << std::setw(20) << opera_state.track_set_state.track_set_state[j].speed
          << std::setw(20) << opera_state.track_set_state.track_set_state[j].distance
          << std::endl;
      std::cout << "radar information ==========================" << std::endl;
      for(std::size_t i=0; i!=opera_state.radar_set_state.radar_set_state.size(); ++i){
        std::cout << std::setw(10) << "radar id: " 
          << std::setw(10) << i; 
        for(std::size_t j=0; j!=opera_state.radar_set_state.radar_set_state[i].targets.size(); ++j){
          std::cout << "["
            << opera_state.radar_set_state.radar_set_state[i].targets[j].x
            << ","
            << opera_state.radar_set_state.radar_set_state[i].targets[j].y
            << "]";
        }
        std::cout << std::endl;
      }
      iter.Next();
      ++tick_cur;
    }
  }
};
} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
}
