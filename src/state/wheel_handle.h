#ifndef TOOLS_STATE_WHEEL_HANDLE_H_
#define TOOLS_STATE_WHEEL_HANDLE_H_

#include <cassert>

namespace tools {

class WheelHandle {
 public:
  WheelHandle(int angle, int x, int y)
      :angle_(angle),
      x_(x),
      y_(y),
      init_(false),
      map_origin_x_(0),
      map_origin_y_(0),
      map_zoom_(0), 
      map_center_longitude_(0.0),
      map_center_latitude_(0.0) {}

  void Initialize();
  inline int map_zoom() { 
    if (!init_) Initialize();
    return map_zoom_; 
  }
  inline double map_center_longitude() { 
    if(!init_) Initialize();
    return map_center_longitude_; 
  }
  inline double map_center_latitude() { 
    if(!init_) Initialize();
    return map_center_latitude_; 
  }
  inline int map_origin_x() {
    if(!init_) Initialize();
    return map_origin_x_;
  }
  inline int map_origin_y() {
    if(!init_) Initialize();
    return map_origin_y_;
  }

private:
  bool init_;
  int angle_;
  int x_;
  int y_;
  int map_origin_x_;
  int map_origin_y_;
  int map_zoom_;
  double map_center_longitude_;
  double map_center_latitude_;
};

} //namespace tools

#endif //TOOLS_STATE_WHEEL_HANDLE_H_
