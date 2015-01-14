#ifndef TOOLS_MAP_MAP_H_
#define TOOLS_MAP_MAP_H_

namespace tools{

class Map{
public:
  inline float origin_x() const { return origin_x_; }
  inline float origin_y() const { return origin_y_; }
  inline int zoom() const { return zoom_; }
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline int center_x() const { return origin_x_ + width_/2; }
  inline int center_y() const { return origin_y_ + height_/2; }

  inline Map& set_zoom(float zoom) { zoom_ = zoom; return *this; }
  inline Map& set_origin_x(float x) { origin_x_ = x; return *this; }
  inline Map& set_origin_y(float y) { origin_y_ = y; return *this; }
  inline Map& zoom(float z){ zoom_ = z; return *this; }
  inline Map& set_width(int width) { width_ =  width; return *this; }
  inline Map& set_height(int height) { height_ = height; return *this; }
  static Map* Instance();
private:
  float zoom_;
  float origin_x_;
  float origin_y_;
  int width_;
  int height_;
  static Map* map_;

  Map(){}
  Map(const Map&);
  Map& operator=(const Map&);
};

} //namespace tools

#endif //TOOLS_MAP_MAP_H_
