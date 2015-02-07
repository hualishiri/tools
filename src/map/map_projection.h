#ifndef TOOLS_MAP_MAP_PROJECTION_H_
#define TOOLS_MAP_MAP_PROJECTION_H_

namespace tools {

class MapProjection {
 public:
  struct PixelPoint {
    double x;
    double y;
  };

  struct WgsPoint {
    double longitude;
    double latitude;
  };

  static MapProjection* Instance(double zoom);

  inline double zoom() { return zoom_; }
  inline MapProjection& set_zoom(double zoom);
  void FromWgsToPixel(const WgsPoint& wgs_point, PixelPoint& pixel_point);
  void FromPixelToWgs(const PixelPoint& pixel_point, WgsPoint& wgs_point);

private:
  const double kSizePixelTile;
  const double kRatioDegreeToRadian;
  const double kRatioRadianToDegree;

  MapProjection(double zoom);

  static MapProjection* map_;

  double zoom_;
  PixelPoint pixel_center_;
  double ratio_xpixel_to_degree_;
  double ratio_ypixel_to_radian_;
};

} //namespace tools

#endif //TOOLS_MAP_MAP_PROJECTION_H_
