#include "opera/line.h"

#include <assert.h>

#include "util/tool.h"

namespace tools {

double Line2D::GetLength() const {
  return sqrt(pow(line_.x, 2) + pow(line_.y, 2));
}

void Line2D::GetPoint(double length, Point2D& point) const {
  assert((length < GetLength() &&  length > 0) ||
      (DoubleEqual(length, GetLength()) || DoubleEqual(length, 0)));
  double radix = length / GetLength();
  point.x = radix * line_.x;
  point.y = radix * line_.y;
}

} //namespace tools
