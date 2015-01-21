#ifndef TOOLS_STATE_DATA_STATE_CIRCLE_H_
#define TOOLS_STATE_DATA_STATE_CIRCLE_H_

namespace tools {

class DataStateCircle {
 public:
  static DataStateCircle* Instance();

 private:
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
    int direction;
  };

  struct Move {
    double x;
    double y;
  };

  DataStateCircle(){}
  DataStateCircle(const DataStateCircle&);
  DataStateCircle& operator=(DataStateCircle&);

  static DataStateCircle* data_;

  Circle circle_;
  Move move_;

  friend class StateTrackCircleStarted;
  friend class StateTrackCircleSelected;
  friend class StateTrackCircleCentered;
  friend class StateTrackCircleSided;
  friend void SetDataLineCircleEclipse(long long id,
                                double start_x,
                                double start_y);
};

} //namespace tools

#endif //TOOLS_STATE_DATA_STATE_CIRCLE_H_
