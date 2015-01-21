#include "tool.h"

#include <assert.h>
#include <iostream>

namespace tools {
namespace test {

class Test{
 public:
   int RunAllTest() {
    TestAngleFromStartByClockInCircle();
   }
   
   int TestAngleFromStartByClockInCircle() {
      double start_x = -5.0;
      double start_y = 0.0;
      double center_x = 0.0;
      double center_y = 0.0;
      double angle_x = 0.0;
      double angle_y = 5.0;
      std::cout << AngleFromStartByClockInCircle(start_x,
                                                 start_y,
                                                 center_x,
                                                 center_y,
                                                 angle_x,
                                                 angle_y)
          << std::endl;
   }
};

}
} //namespace tools

int main() {
  return tools::test::Test().RunAllTest();
}
