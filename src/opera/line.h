#ifndef TOOLS_OPERA_LINE_H_
#define TOOLS_OPERA_LINE_H_

#include "opera/shape.h"

namespace tools {

class Line2D : public Shape2D {
 public:
  // line cannot equal {0.0, 0.0}
  Line2D(const Point2D& line) : line_(line) {}
  virtual double GetLength() const;
  virtual void GetPoint(double length, Point2D& point) const;

 private:
  Point2D line_;    //vector of line
};

} //namespace tools

#endif //TOOLS_OPERA_LINE_H_
