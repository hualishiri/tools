#ifndef TOOLS_OPERA_ECLIPSE_H_
#define TOOLS_OPERA_ECLIPSE_H_

#include "opera/shape.h"

namespace tools {

class Eclipse2D : public Shape2D {
 public:
  //major cannot be {0.0, 0.0}, minor cannot be equal to major and {0.0 , 0.0}
  //angle must be greater than -2*PI and less than 2*PI
  Eclipse2D(const Point2D& major, const Point2D& minor, float angle)
      :semi_major_(major), semi_minor_(minor), angle_(angle) {
  }

  virtual double GetLength() const;
  virtual void GetPoint(double length, Point2D& point) const;

 private:
  double Length(const Point2D& p) const;
  double Angle(double x, double y) const;

  Point2D semi_major_;
  Point2D semi_minor_;
  float angle_;
};

} //namespace tools

#endif //TOOLS_OPERA_ECLIPSE_H_
