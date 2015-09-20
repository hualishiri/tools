#ifndef TOOLS_OPERA_OPERA_OPTION_H_
#define TOOLS_OPERA_OPERA_OPTION_H_

#include <assert.h>

#include <vector>
#include <string>
#include <iostream>

namespace tools {

class OperaOption {
 public:
  friend std::ostream& operator<< (std::ostream& os, const OperaOption& op);
  friend std::istream& operator>> (std::istream& in, OperaOption& op);

  enum TrackUnitType { 
      //直线
      LINE=0,

      //圆
      CIRCLE                
  };

  enum RadarType {
      //静态雷达 
      R_STATIC=0,
      
      //动态雷达
      R_DYNAMIC
  };

  enum ObjectType { 
      AIRCRAFT=1,         //空中目标
      LANDCRAFT=2,        //陆地、水面目标
      UNDERCRAFT=4        //水下目标
  };

    struct Error {
      double error_random_distance;       //随机误差:距离，单位：由使用者决定
      double error_random_azimuth;        //随机误差：方位角，单位：度
      double error_random_elevation;      //随机误差：俯仰角，单位：度
      double error_system_distance;       //系统误差:距离，单位：由使用者决定
      double error_system_azimuth;        //系统误差：方位角，单位：度
      double error_system_elevation;      //系统误差：俯仰角，单位：度
      
    };

  struct Radar {
    long long id;

    //雷达类型，取值范围： RadarType类型
    //注意：该字段不能直接操作，需要通过函数操作
    int type;                         

    //雷达探测目标类型，取值范围:ObjectType
    int detecting_objects_types;

    //当type的取值为：R_DYNAMIC时有效，表示雷达的轨迹
    int track_id;

    //单位：由使用者决定
    double start_x;
    double start_y;
    double radius_x;
    double radius_y;

    //雷达的系统误差
    struct Error error;   

    //雷达的伞扫范围，<起始方位角，范围>
    std::vector<std::pair<double, double> > azimuth_range; 

    //type字段的Getter和Ｓｅｔｔｅｒ
    void set_type(RadarType radar_type);
    RadarType get_type() const;

    //无意义的操作函数
    void set_type_trival(unsigned char type);
    unsigned char get_type_trival(void) const;
  };
  
  struct Line {
    long long id;

    //单位：由使用者决定
    double start_x;
    double start_y;
    double end_x;
    double end_y;
  };
  
  struct Circle {
    long long id;

    //单位：由使用者决定
    double start_x;
    double start_y;
    double center_x;
    double center_y;

    //单位：度，该变量有方向.范围：[-2.0*PI, 2.0*PI]
    double angle;
  };
  

  struct Track {
    //该批量轨迹ID，无用
    long long id;

    struct Reserve {
        int data[5]; //标示轨迹所绑定的目标实际类型,飞机，火箭
        int type; //标示多个轨迹是相同的
    } reserve;

    //目标的初始速度，单位：由使用者决定
    std::vector<double> start_speeds;

    //目标的加速度，单位：由使用者决定
    std::vector<std::vector<float> > accelerations;
    
    //每条轨迹的延迟时间，单位：秒
    std::vector<double> time_delays;

    //目标的批次
    short batch_count;

    //同一批次的目标初始位置的随机噪声
    double level_noise_track;

    //每个目标的ID
    std::vector<long long> ids;
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<TrackUnitType> types;

    //目标类型，取值：ObjectType
    std::vector<int> track_types;
  };

  //内部使用的变量
  struct TrackInternal {
    long long id;
    double start_speed;
    std::vector<float> acceleration;
    double time_delay;
    int track_type;
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<TrackUnitType> types;
  };

  static OperaOption* Instance();

  OperaOption() : interval_(0.1) {}
  void push_back_radar(Radar& radar);
  void pop_radar(long long id);
  inline std::size_t size_radar() const { return radars_.size(); }
  void push_back_track(Track& track);
  inline std::size_t size_track() const { return tracks_.size(); }

  inline std::vector<Radar> radars() const { return radars_; }
  std::vector<TrackInternal> tracks() const;
  std::vector<Track> get_tracks() const { return tracks_; }

  inline void clear_radars() { radars_.clear(); }
  inline void clear_tracks() { tracks_.clear(); }
  inline void clear() {
    clear_radars();
    clear_tracks();
  }

  inline void set_interval(double interval) { interval_ = interval; }
  inline double interval() const { return interval_; } 

  int get_reserve_of_track(long long id, int index) const;

  void ConvertToPixel();
  void ConvertToPlaneCoodinate(void (*)(double*, double*));

  bool operator==(const OperaOption& opera_option) const;

  std::vector<int> get_track_types() const;
  std::vector<Track> get_tracks_by_type(int type) const;
  
 private:
  void TrackInternalSift(TrackInternal& track_internal,
                         double level_noise,
                         int seed) const;
  bool IsIDUnique() const;
  bool IsIDExistInTrackSet(long long id) const;

  static OperaOption* opera_option_;

  //迭代的步长，单位：秒
  double interval_;


  std::vector<Radar> radars_;
  std::vector<Track> tracks_;
};

std::ostream& operator<< (std::ostream& os, const OperaOption& op);
std::istream& operator>> (std::istream& in, OperaOption& op);

} //namespace tools

#endif //TOOLS_OPERA_OPERA_OPTION_H_
