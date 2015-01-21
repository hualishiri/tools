#include "state/wheel_handle.h"

#include "map/map.h"
#include "map/map_projection.h"
#include "util/tool.h"

namespace tools {
namespace test {

int new_zoom(int);

class Test {
 public:
  int RunAllTest() {
    int sum = 0;
    TestWheelHandle();
    return 0;
  }
  int TestWheelHandle(){
    //wheel
    int angle = 120;
    int x = 100;
    int y = 100;

    //map
    int zoom = 10;
    int origin_x = 1431;
    int origin_y = 14329;
    int width = 100;
    int height = 200;

    WheelHandle wheel_handle(angle, x, y);
    assert(new_zoom(angle) == wheel_handle.map_zoom());

    MapProjection::PixelPoint pixel_point;
    MapProjection::WgsPoint wgs_point;
    pixel_point.x = origin_x + x;
    pixel_point.y = origin_y + y;
    MapProjection::Instance(zoom)->FromPixelToWgs(pixel_point, wgs_point);
    MapProjection::Instance(new_zoom(angle))->FromWgsToPixel(
        wgs_point, pixel_point);
    assert(wheel_handle.map_origin_x() == pixel_point.x - x);
    assert(wheel_handle.map_origin_y() == pixel_point.y - y);
    
    pixel_point.x = pixel_point.x - x + width / 2;
    pixel_point.y = pixel_point.y - y + height / 2;

    MapProjection::Instance(new_zoom(angle))->FromPixelToWgs(
        pixel_point, wgs_point);
    assert(DoubleEqual(wgs_point.longitude, 
                       wheel_handle.map_center_longitude()));
    assert(DoubleEqual(wgs_point.latitude,
                       wheel_handle.map_center_latitude()));
    return 0;
  }

};

int new_zoom(int angle){ return Map::Instance()->zoom() + angle / 120; }

} //namespace test
} //namespace tools

int main(){
  return tools::test::Test().RunAllTest();
}
