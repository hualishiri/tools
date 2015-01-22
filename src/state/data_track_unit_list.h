#ifndef TOOLS_STATE_DATA_TRACK_UNIT_LIST_H_
#define TOOLS_STATE_DATA_TRACK_UNIT_LIST_H_

#include <vector>

#include "opera_option.h"

namespace tools {

class DataTrackUnitList {
 public:
  enum TrackUnitType { LINE, CIRCLE, ECLIPSE };

  static DataTrackUnitList* Instance();

  void push_back_line(long long id, double end_x, double end_y);
  void push_back_circle(long long id,
                        double center_x,
                        double center_y,
                        double side_x,
                        double size_y, 
                        double angle_x,
                        double angle_y);
  void push_back_eclipse(long long id,
                         double center_x,
                         double center_y, 
                         double end_x,
                         double end_y,
                         double side_x,
                         double side_y, 
                         double angle_x,
                         double angle_y);
  inline void set_id(long long id) { id_ = id; }
  inline void set_start(double x, double y) { 
    start_x_ = x;
    start_y_ = y;
  }
  inline double start_x() const { return start_x_; }
  inline double start_y() const { return start_y_; }
  inline void clear() {
    units_.clear();
    units_id_.clear();
    units_flag_.clear();
  }
  inline bool empty() const { return units_.empty(); }
  inline std::size_t size() const { return units_.size(); }
  inline std::vector<double> track_units() const { return units_; }
  OperaOption::Track track() const;

 private:
  DataTrackUnitList() : start_x_(0.0), start_y_(0.0), id_(0) {}
  DataTrackUnitList(const DataTrackUnitList&);
  DataTrackUnitList& operator=(const DataTrackUnitList&);

  static DataTrackUnitList* data_;
  
  double id_;
  double start_x_;
  double start_y_;
  std::vector<int> units_flag_;
  std::vector<long long> units_id_;
  std::vector<double> units_;
};

} //namespace tools

#endif //TOOLS_STATE_DATA_TRACK_UNIT_LIST_H_
