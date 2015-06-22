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
      LINE=0,             //直线
      CIRCLE              //园  
  };
  enum RadarType { 
      R_STATIC=0,         //静态雷达
      R_DYNAMIC           //动态雷达
  };
  enum ObjectType { AIRCRAFT=1, LANDCRAFT=2, UNDERCRAFT=4 };

    struct Error {
      double error_random_distance;
      double error_random_azimuth;
      double error_random_elevation;
      double error_system_distance;
      double error_system_azimuth;
      double error_system_elevation;
    };

  struct Radar {
    long long id;

    //RadarType
    int type;

    //The 'or' operators of ObjectType values
    int detecting_objects_types;

    //The value of OperaOption::Track::ids
    int track_id;

    double start_x; // longitude by degree
    double start_y; // latitude by degree
    double radius_x;
    double radius_y;
    struct Error error;

    std::vector<std::pair<double, double> > azimuth_range; 

    void set_type(RadarType radar_type);
    RadarType get_type() const;
    void set_type_trival(unsigned char type);
    unsigned char get_type_trival(void) const;
  };
  
  struct Line {
    long long id;
    double start_x;
    double start_y;
    double end_x;
    double end_y;
  };
  
  struct Circle {
    long long id;
    double start_x;
    double start_y;
    double center_x;
    double center_y;
    double angle;
  };
  
  struct Track {
    long long id;
    std::vector<double> start_speeds;
    std::vector<std::vector<float> > accelerations;
    std::vector<double> time_delays;
    short batch_count;
    double level_noise_track;
    std::vector<long long> ids;
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<TrackUnitType> types;

    //The 'or' operators of ObjectType values
    std::vector<int> track_types;
  };

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

  void ConvertToPixel();
  void ConvertToPlaneCoodinate(void (*)(double*, double*));

  bool operator==(const OperaOption& opera_option) const;
  
 private:
  void TrackInternalSift(TrackInternal& track_internal,
                         double level_noise,
                         int seed) const;
  bool IsIDUnique() const;
  bool IsIDExistInTrackSet(long long id) const;

  static OperaOption* opera_option_;

  double interval_;
  std::vector<Radar> radars_;
  std::vector<Track> tracks_;
};

std::ostream& operator<< (std::ostream& os, const OperaOption& op);
std::istream& operator>> (std::istream& in, OperaOption& op);

} //namespace tools

#endif //TOOLS_OPERA_OPERA_OPTION_H_
