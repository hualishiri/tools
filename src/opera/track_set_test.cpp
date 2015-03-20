#include "track_set.h"

#include "opera/acceleration.h"
#include "opera/shape.h"
#include "opera/line.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class TRACKSET {};

TEST(TRACKSET, Iterator) {
  double location[] = {
    116.420654, 39.857135,  //北京
    117.210526, 39.136095,/*  //天津
    121.471514, 31.236071,*/  //上海
    87.444049, 43.812134/*,	//乌鲁木齐
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
    108.895294,	34.420422	//西安*/
  };
  int len = sizeof(location)/sizeof(double)/2;
  float init_speed = 0.002f;
  float interval = 10.0f;
  Acceleration* acc_uniform = new UniformAcceleration();
  TrackSet2D::TrackSet track_set_rep;
  unsigned long long index = 0xdeadbeef00000001;
  for(int i=0; i!=len; ++i){
    for(int j=0; j!=len; ++j){
      if(i == j) continue;
        double bias_x = location[j*2] - location[i*2];
        double bias_y = location[j*2+1] - location[i*2+1];
        Shape2D* line = new Line2D(Point2D(bias_x, bias_y));
        TrackUnit* track_unit = new TrackUnit(line,
                                              acc_uniform,
                                              interval,
                                              init_speed);
        Track2D::TrackUnitSet* track_unit_set1 = new Track2D::TrackUnitSet();
        track_unit_set1->push_back(track_unit);
        Track2D* track = new Track2D(index++,
                                     track_unit_set1,
                                     interval,
                                     init_speed);
        track_set_rep.push_back(track);
    }
  }
    TrackSet2D::TrackSetPosition track_set_position;
    int num_of_track = len*(len-1);
    int index_i = 0;
    for(int i = 0; i != num_of_track; ++i){
      index_i = i / (len-1);
      track_set_position.push_back(new Point2D(location[index_i*2],
                                               location[index_i*2+1]));
      LogDebug("Track Init Position: ID：%d\t(%f,%f)]",
               i,
               location[index_i * 2],
               location[index_i * 2 + 1]);
    }
    TrackSet2D track_set(&track_set_rep, &track_set_position, interval);
    LogDebug("Track Set Infomation");
    for(std::size_t i=0; i!=track_set_rep.size(); ++i){
      LogDebug("Track ID : %X\tLength:%f", i + 1, track_set_rep[i]->GetLength());
    }

    TrackSet2D::Iterator iter(&track_set);
    TrackSet2D::TrackSetState track_set_state;
    int count = 0;
    while(iter.Valid()){
      iter.Value(track_set_state);
      LogDebug("Track NO.\tPosition\tTime\tAcceleration\tSpeed\tDistance\n");
      for(std::size_t i = 0; i != track_set_state.track_set_state.size(); ++i)
        LogDebug("ID:0x%X\tPOS:(%f,%f)\tT:%d\tA:%f\tS:%f\tD:%f",
                 track_set_state.track_set_state[i].id,
                 track_set_state.track_set_state[i].point.x,
                 track_set_state.track_set_state[i].point.y,
                 track_set_state.track_set_state[i].tick,
                 track_set_state.track_set_state[i].acc,
                 track_set_state.track_set_state[i].speed,
                 track_set_state.track_set_state[i].distance);
      iter.Next();
      ++count;
    }
    LogDebug("Track Set Sum Count: %d", count);
    LogDebug("Track Set Max Sum Tick: %d", track_set.GetSumTick());
    LogDebug("Track Set Max Length: %f", track_set.GetSumLength());
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
