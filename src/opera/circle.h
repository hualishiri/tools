#ifndef TOOLS_OPERA_CIRCLE_H_
#define TOOLS_OPERA_CIRCLE_H_

#include "opera/shape.h"

namespace  tools {

class Circle2D : public Shape2D {
 public:
  //p cannot be {0.0, 0.0}, angle is greater than -2*PI and less than 2*PI 
  Circle2D(const Point2D& p, float angle)
      : center_(p), angle_(angle), radius_(Length(center_)) {
  }
  virtual double GetLength() const;
  virtual void GetPoint(double length, Point2D& point) const;

 private:
  double Length(const Point2D& p) const;
  //Angle return [0,2*PI]
  double Angle(double x, double y) const;

  Point2D center_;  //vector from start point to radius
  float angle_; //the angle that neet to cut, plus stant for clock direction, or un-clock direction
  //float angle_bise_;
  double radius_;
};

}

#endif //TOOLS_OPERA_CIRCLE_H_
