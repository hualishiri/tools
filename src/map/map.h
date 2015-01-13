#ifndef TOOLS_MAP_MAP_H_
#define TOOLS_MAP_MAP_H_

namespace tools{

class Map{
public:
  inline float origin_x() const { return origin_x_; }
  inline float origin_y() const { return origin_y_; }
  inline int zoom() const { return zoom_; }
  inline void set_zoom(float zoom) { zoom_ = zoom; }
  inline void set_origin_x(float x) { origin_x_ = x; }
  inline void set_origin_y(float y) { origin_y_ = y; }
  inline void zoom(float z){ zoom_ = z; }
  static Map* Instance();
private:
  float zoom_;
  float origin_x_;
  float origin_y_;
  static Map* map_;
  Map(){}
};

} //namespace tools

#endif //TOOLS_MAP_MAP_H_
