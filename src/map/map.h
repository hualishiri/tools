#ifndef TOOLS_MAP_MAP_H_
#define TOOLS_MAP_MAP_H_

namespace tools {

class Map {
 public:
  static Map* Instance();
  
  inline double origin_x() const { return origin_x_; }
  inline double origin_y() const { return origin_y_; }
  inline int zoom() const { return zoom_; }
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline int center_x() const { return origin_x_ + width_ / 2; }
  inline int center_y() const { return origin_y_ + height_ / 2; }

  inline Map& set_zoom(int zoom) {
    zoom_ = zoom;
    return *this;
  }
  inline Map& set_origin_x(double x) {
    origin_x_ = x;
    return *this;
  }
  inline Map& set_origin_y(double y) {
    origin_y_ = y;
    return *this;
  }
  inline Map& zoom(double z){
    zoom_ = z;
    return *this;
  }
  inline Map& set_width(int width) {
    width_ =  width;
    return *this;
  }
  inline Map& set_height(int height) {
    height_ = height;
    return *this;
  }

 private:
  Map() {}
  Map(const Map&);
  Map& operator=(const Map&);

  static Map* map_;

  int zoom_;
  double origin_x_;
  double origin_y_;
  int width_;
  int height_;
};

} //namespace tools

#endif //TOOLS_MAP_MAP_H_
