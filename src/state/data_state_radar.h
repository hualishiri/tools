#ifndef TOOLS_STATE_DATA_STATE_RADAR_H_
#define TOOLS_STATE_DATA_STATE_RADAR_H_

namespace tools {

class DataStateRadar {
 private:
  DataStateRadar() 
      : center_x_(0),
      center_y_(0),
      move_x_(0),
      move_y_(0),
      id_(0) {}

  static DataStateRadar* Instance();

  inline long long id() const { return id_; }
  inline double center_x() const { return center_x_; }
  inline double center_y() const { return center_y_; }
  inline double move_x() const { return move_x_; }
  inline double move_y() const { return move_y_; }
  inline void set_id(long long id){ id_ = id; }
  inline void set_move(double x, double y) {
    move_x_ = x;
    move_y_ = y;
  }
  inline void set_center(double x, double y) {
    center_x_ = x;
    center_y_ = y;
  }

  static DataStateRadar* data_;

  long long id_;
  double center_x_;
  double center_y_;
  double move_x_;
  double move_y_;

  friend class StateRadarSelected;
  friend class StateRadarCentered;
};

} //namespace tools

#endif //TOOLS_STATE_DATA_STATE_RADAR_H_
