#include "opera/line.h"

#include <vector>

#include "util/testharness.h"
#include "util/tool.h"

namespace tools {

class LINE {};

TEST(LINE, GetLength) {
  std::vector<Shape2D*> point_pointer;

  for (int i = -20; i != 20; ++i) {
    for (int j = -20; j != 20; ++j) {
    Shape2D* line = new Line2D(Point2D(i, j));
    for (int k = 0; k <= line->GetLength(); ++k) {
      Point2D temp(0.0, 0.0);
      line->GetPoint(k, temp);
      if (i == 0 && j == 0)
        continue;
      ASSERT_TRUE(DoubleEqual(temp.x, i * k / line->GetLength()));
      ASSERT_TRUE(DoubleEqual(temp.y, j * k / line->GetLength()));
    }
    ASSERT_TRUE(DoubleEqual(line->GetLength(), sqrt(i * i + j * j)));   
    delete line;
    }
  }
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
