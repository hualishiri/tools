#ifndef TOOLS_OPERA_SHAPE_H_
#define TOOLS_OPERA_SHAPE_H_

#include <math.h>

namespace tools {

struct Point2D {
  Point2D() : x(0.0), y(0.0) {}
  Point2D(double a, double b) : x(a), y(b) {}

  double x;
  double y;
};

struct PointState2D {
  Point2D point;  
  float speed;
  float acc;
  long long tick;
  long long time;
};

class Shape2D {
 public:
  virtual ~Shape2D() {}
  virtual double GetLength() const = 0;
  //length >= 0 and less than GetLength() or equal GetLength()
  virtual void GetPoint(double length, Point2D& point) const = 0;
};

} //namespace tools

#endif //TOOLS_OPERA_SHAPE_H_
