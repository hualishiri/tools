#include "opera.h"

#include <iostream>
#include <iomanip>

namespace test{
class Test{
public:
  void RunAllTest(){
    FunctionTest();
  }
  void FunctionTest(){
    double location[] = {
116.420654, 39.857135,  //北京
117.210526, 39.136095,  //天津
121.471514, 31.236071,  //上海
87.444049, 43.812134,	//乌鲁木齐
91.049919, 29.867456,	//拉萨
112.059632, 3.903721,	//曾母暗沙
110.293492, 20.108493,	//海口
121.552637, 25.161594,	//台北
119.271372, 26.095614,	//福州
115.959859, 28.689981,	//南昌
112.979495, 28.332455,	//长沙
114.304102, 30.713661,	//武汉
117.137286, 31.945469,	//合肥
113.6418, 34.755164,	//郑州
126.630291, 45.712474,	//哈尔滨
111.654892, 40.90659,	//呼和浩特
106.209292, 38.230189,	//银川
102.640216, 25.1281,	//昆明
103.928027, 30.681863,	//成都
108.895294,	34.420422	//西安
    };
    std::cout << std::setprecision(12) << location[0] << std::endl;
    int len = sizeof(location)/sizeof(double)/2;
    float init_speed = 0.02f;
    float interval = 10.0f;
    tools::Acceleration* acc_uniform = new tools::UniformAcceleration();
    tools::Acceleration* acc_constant = new tools::ConstantAcceleration(0.0000001);
    tools::TrackSet2D::TrackSet *track_set_rep = new tools::TrackSet2D::TrackSet();
    unsigned long long index = 0xdeadbeef00000001;
    for(int i=0; i!=len; ++i){
      for(int j=0; j!=len; ++j){
        if(i == j) continue;
        double bias_x = location[j*2] - location[i*2];
        double bias_y = location[j*2+1] - location[i*2+1];
        tools::Shape2D* line = new tools::Line2D(tools::Point2D(bias_x, bias_y));
        tools::Shape2D* line1 = new tools::Line2D(tools::Point2D(bias_x/2.0, bias_y/2.0));
        tools::Shape2D* line2 = new tools::Line2D(tools::Point2D(bias_x/2.0, bias_y/2.0));
        tools::TrackUnit* track_unit = new tools::TrackUnit(line, acc_uniform, interval, init_speed);
        tools::TrackUnit* track_unit1 = new tools::TrackUnit(line1, acc_uniform, interval, init_speed);
        tools::TrackUnit* track_unit2 = new tools::TrackUnit(line2, acc_constant, interval, track_unit1->GetEndSpeed());
        tools::Track2D::TrackUnitSet* track_unit_set = new tools::Track2D::TrackUnitSet();
        tools::Track2D::TrackUnitSet* track_unit_set1 = new tools::Track2D::TrackUnitSet();
        track_unit_set->push_back(track_unit1);
        track_unit_set->push_back(track_unit2);
        track_unit_set1->push_back(track_unit);
        tools::Track2D* track = new tools::Track2D(index++, track_unit_set, interval, init_speed);
        track_set_rep->push_back(track);
      }
    }
    tools::TrackSet2D::TrackSetPosition* track_set_position
      = new tools::TrackSet2D::TrackSetPosition();;
    int num_of_track = len*(len-1);
    int index_i = 0;
    for(int i = 0; i != num_of_track; ++i){
      index_i = i / (len-1);
      track_set_position->push_back(new tools::Point2D(location[index_i*2], location[index_i*2+1]));
      std::cout << "[" << location[index_i*2] << "," << location[index_i*2+1] << "]";
    }
    std::cout << std::endl;
    tools::TrackSet2D* track_set = new tools::TrackSet2D(track_set_rep, track_set_position, interval);
    //init finished
    //
    //
    tools::RadarSet2D::RadarSet* rep_radar_set = new tools::RadarSet2D::RadarSet();
    for(int i=0; i!=len; ++i)
      rep_radar_set->push_back(new tools::MechanicalRadar2D(index++, location[2*i], location[2*i+1], 1));
    tools::RadarSet2D* radar_set = new tools::RadarSet2D(rep_radar_set); 
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    tools::Opera2D* opera = new tools::Opera2D(track_set, radar_set);

    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    tools::Opera2D::Iterator *iter = new tools::Opera2D::Iterator(opera);
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
    tools::Opera2D::OperaState *opera_state = new tools::Opera2D::OperaState();
    long long tick_cur = 1;
    while(iter->Valid()){
      std::cout << "==============================================="<< std::endl;
      //一次时间迭代
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
      iter->Value(*opera_state);
      std::cout << "track numbers: " << opera_state->track_set_state.track_set_state.size()
        << std::endl;
      std::cout << std::setw(20) << "tick_no" 
      << std::setw(20) << "track_no"
      << std::setw(20) << "position"
      << std::setw(20) << "time"
      << std::setw(20) << "acc"
      << std::setw(20) << "speed"
      << std::setw(20) << "distance" << std::endl;
        for(std::size_t j = 0; j != opera_state->track_set_state.track_set_state.size(); ++j)
          std::cout << std::setw(20) << tick_cur
          << std::setw(20) << std::hex << opera_state->track_set_state.track_set_state[j].id << " "
          << std::setprecision(12) << opera_state->track_set_state.track_set_state[j].point.x << ","
          << std::setprecision(12) << opera_state->track_set_state.track_set_state[j].point.y
          << std::setw(20) << std::dec << opera_state->track_set_state.track_set_state[j].tick 
          << std::setw(20) <<  opera_state->track_set_state.track_set_state[j].acc 
          << std::setw(20) << opera_state->track_set_state.track_set_state[j].speed
          << std::setw(20) << opera_state->track_set_state.track_set_state[j].distance
          << std::endl;
      std::cout << "radar information ==========================" << std::endl;
      for(std::size_t i=0; i!=opera_state->radar_set_state.radar_set_state.size(); ++i){
        std::cout << std::setw(10) << "radar id: " 
          << std::setw(10) << std::hex << opera_state->radar_set_state.radar_set_state[i].id
          << " " << "[" << opera_state->radar_set_state.radar_set_state[i].point.x
          << "," << opera_state->radar_set_state.radar_set_state[i].point.y << "]" << std::endl;
        for(std::size_t j=0; j!=opera_state->radar_set_state.radar_set_state[i].targets.size(); ++j){
          std::cout << "["
            << opera_state->radar_set_state.radar_set_state[i].targets[j].x
            << ","
            << opera_state->radar_set_state.radar_set_state[i].targets[j].y
            << "]";
        }
        std::cout << std::endl;
      }
    ////////////////////////////////////////////////
    ////////////////////////////////////////////////
      iter->Next();
      ++tick_cur;
    }
  }
};
} //namespace test

int main(){
  test::Test().RunAllTest();
}
