#ifndef TOOLS_STATE_OPERA_OPTION_H_
#define TOOLS_STATE_OPERA_OPTION_H_

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
    long long id;
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<Eclipse> eclipses;
    std::vector<TrackUnitType> types;
  };

  static OperaOption* Instance();

  inline void push_back_radar(const Radar& radar){ radars_.push_back(radar); }
  void pop_radar(long long id);
  inline std::size_t size_radar() const { return radars_.size(); }
  inline void push_back_object(const Object& object) {
    objects_.push_back(object);
  }
  void pop_object(long long id);
  inline std::size_t size_object() const { return objects_.size(); }
  inline void push_back_track(const Track& track) { tracks_.push_back(track); }
  void pop_track(long long id);
  inline std::size_t size_track() const { return tracks_.size(); }

  inline std::vector<Radar> radars() const { return radars_; }
  inline std::vector<Object> objects() const { return objects_; }
  inline std::vector<Track> tracks() const { return tracks_; }
  
 private:
  OperaOption() {}
  OperaOption(const OperaOption&);
  OperaOption& operator=(const OperaOption&);

  static OperaOption* option_;

  std::vector<Radar> radars_;
  std::vector<Object> objects_;
  std::vector<Track> tracks_;
};

} //namespace tools

#endif //TOOLS_STATE_OPERA_OPTION_H_
