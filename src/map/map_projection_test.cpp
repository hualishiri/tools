#include "map_projection.h"

#include <iostream>

namespace tools {
namespace test {

class Test {
 public:
  void RunAllTest() {
    TestMapProjection();
  }

  void TestMapProjection() {
    MapProjection::PixelPoint pixel_point;
    MapProjection::WgsPoint wgs_point;
    wgs_point.longitude = -88.233735;
    wgs_point.latitude =   31.46484;
    MapProjection::Instance(5)->FromWgsToPixel(wgs_point, pixel_point);
    std::cout << pixel_point.x << " " << pixel_point.y << std::endl;
  }
};

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
  return 0;
}
