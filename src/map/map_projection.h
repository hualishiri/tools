#ifndef TOOLS_MAP_MAP_PROJECTION_H_
#define TOOLS_MAP_MAP_PROJECTION_H_

namespace tools{

class MapProjection{
public:
  struct PixelPoint{
    double x;
    double y;
  };
  struct WgsPoint{
    double longitude;
    double latitude;
  };
  inline double zoom() { return zoom_; }
  inline MapProjection& set_zoom(double zoom);
  void FromWgsToPixel(const WgsPoint& wgs_point, PixelPoint& pixel_point);
  void FromPixelToWgs(const PixelPoint& pixel_point, WgsPoint& wgs_point);
  static MapProjection* Instance(double zoom);
private:
  MapProjection(double zoom);
  double zoom_;
  const double size_pixel_tile_;
  const double ratio_degree_to_radian_;
  const double ratio_radian_to_degree_;
  PixelPoint pixel_center_;
  double ratio_xpixel_to_degree_;
  double ratio_ypixel_to_radian_;

  static MapProjection* map_;
};

} //namespace tools

#endif //TOOLS_MAP_MAP_PROJECTION_H_
