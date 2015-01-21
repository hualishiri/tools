#ifndef TOOLS_STATE_DATA_STATE_LINE_H_
#define TOOLS_STATE_DATA_STATE_LINE_H_

namespace tools {

class DataStateLine {
 private:
  DataStateLine() 
      : id_(0),
      start_x_(0.0),
      start_y_(0.0),
      move_x_(0.0), 
      move_y_(0.0) {}

  static DataStateLine* Instance();

  inline long long id() const { return id_; }
  inline double start_x() const { return start_x_; }
  inline double start_y() const { return start_y_; }
  inline double move_x() const { return move_x_; }
  inline double move_y() const { return move_y_; }
  inline void set_id(long long id) { id_ = id; }
  inline void set_start(double x, double y) {
    start_x_ = x;
    start_y_ = y;
  }
  inline void set_move(double x, double y) {
    move_x_ = x;
    move_y_ = y;
  }

  static DataStateLine* data_;

  long long id_;
  double start_x_;
  double start_y_;
  double move_x_;
  double move_y_;

  friend class StateTrackLineSelected;
  friend class StateTrackLineStarted;
  friend void SetDataLineCircleEclipse(long long id,
                                       double start_x,
                                       double start_y);
};

} //namespace tools

#endif //TOOLS_STATE_DATA_STATE_LINE_H_
