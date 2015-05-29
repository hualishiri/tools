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

  enum TrackUnitType { LINE=0, CIRCLE, ECLIPSE };
  enum RadarType {R_STATIC=0, R_DYNAMIC};

  struct Radar {
    long long id;

    //RadarType
    int type;

    //The value of OperaOption::Track::ids
    int track_id;

    double start_x; // longitude by degree
    double start_y; // latitude by degree
    double radius_x;
    double radius_y;
    double level_noise;
    double error_system;
    double error_random;;
    double error_overall;
    std::vector<std::pair<double, double> > azimuth_range; 
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
  };

  struct TrackInternal {
    long long id;
    double start_speed;
    std::vector<float> acceleration;
    double time_delay;
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
