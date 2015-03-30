#ifndef TOOLS_OPERA_OPERA_OPTION_H_
#define TOOLS_OPERA_OPERA_OPTION_H_

#include <assert.h>

#include <vector>

namespace tools {

class OperaOption {
 public:
  enum TrackUnitType { LINE, CIRCLE, ECLIPSE };
  struct Radar {
    long long id;
    unsigned char type;
    double start_x;
    double start_y;
    double radius_x;
    double radius_y;
    double level_noise;
    double angle_azimuth;
    double angle_sector_range;
  };
  
  struct Object {
    long long id;
    unsigned char type;
    double x;
    double y;
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
    double side_x;
    double side_y;
    double angle_x;
    double angle_y;
  };
  
  struct Eclipse {
    long long id;
    double start_x;
    double start_y;
    double center_x;
    double center_y;
    double end_x;
    double end_y;
    double side_x;
    double side_y;
    double angle_x;
    double angle_y;
  };
  
  struct Track {
    double start_speed;
    double acceleration;
    double time_delay;
    short batch_count;
    std::vector<long long> ids;
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<Eclipse> eclipses;
    std::vector<TrackUnitType> types;
  };

  struct TrackInternal {
    long long id;
    double start_speed;
    double acceleration;
    double time_delay;
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<Eclipse> eclipses;
    std::vector<TrackUnitType> types;
  };

  static OperaOption* Instance();

  OperaOption() : interval_(0.1) {}
  void push_back_radar(Radar& radar) { radars_.push_back(radar); }
  void pop_radar(long long id);
  inline std::size_t size_radar() const { return radars_.size(); }
  void push_back_object(Object& object) { objects_.push_back(object); }
  void pop_object(long long id);
  inline std::size_t size_object() const { return objects_.size(); }
  void push_back_track(Track& track) {
    std::size_t track_unit_size = track.lines.size() 
        + track.circles.size() + track.eclipses.size();
    assert( track_unit_size == track.types.size());
    assert(track.ids.size() == static_cast<std::size_t>(track.batch_count));
    tracks_.push_back(track); 
  }
  inline std::size_t size_track() const { return tracks_.size(); }

  inline std::vector<Radar> radars() const { return radars_; }
  inline std::vector<Object> objects() const { return objects_; }
  inline std::vector<TrackInternal> tracks() const { 
    std::vector<TrackInternal> track_internals;
    std::size_t track_batch_count = 0;
    for (std::size_t i=0; i!=tracks_.size(); ++i) {
      track_batch_count = static_cast<std::size_t>(tracks_[i].batch_count);
      for (std::size_t j=0; j!=track_batch_count; ++j) {
        TrackInternal track_internal = {
          tracks_[i].ids[j],
          tracks_[i].start_speed,
          tracks_[i].acceleration,
          tracks_[i].time_delay,
          tracks_[i].lines,
          tracks_[i].circles,
          tracks_[i].eclipses,
          tracks_[i].types
        };
        track_internals.push_back(track_internal);
      }
    }
    return track_internals;
  }

  inline void clear_radars() { radars_.clear(); }
  inline void clear_objects() { objects_.clear(); }
  inline void clear_tracks() { tracks_.clear(); }
  inline void clear() {
    clear_radars();
    clear_objects();
    clear_tracks();
  }

  inline void set_interval(double interval) { interval_ = interval; }
  inline double interval() const { return interval_; } 

  void ConvertToPixel();
  
 private:
  static OperaOption* opera_option_;

  double interval_;
  std::vector<Radar> radars_;
  std::vector<Object> objects_;
  std::vector<Track> tracks_;
};

} //namespace tools

#endif //TOOLS_OPERA_OPERA_OPTION_H_
