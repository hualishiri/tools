#define private public
#include "state_radar_selected.h"

#include <assert.h>
#include <string.h>

#include <sstream>
#include <iostream>

#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "webkit/webkit.h"
#include "state/data_state_radar.h"
#include "state/opera_context.h"
#include "state/state.h"
#include "util/tool.h"

namespace tools{
namespace test{
namespace{

double g_longitude;
double g_latitude;

} //namespace

void page(const char*);

class Test{
 public:
  int RunAllTest() {
    int sum = 0;
    sum += TestStateRadarSelected();
    return sum;
  }

  int TestStateRadarSelected() {
    int left_x = 200;
    int left_y = 400;

    Map::Instance()->set_zoom(6);
    Map::Instance()->set_origin_x(412);
    Map::Instance()->set_origin_y(412);
    Map::Instance()->set_width(1000);
    Map::Instance()->set_height(500);

    Webkit::Instance()->set_page(page);
    State* state = new StateRadarSelected();
    OperaContext opera_context(state);
    EventReleaseLeft::Instance()->set(left_x, left_y);
    MapProjection::PixelPoint pixel_point;
    MapProjection::WgsPoint wgs_point;
    pixel_point.x = Map::Instance()->origin_x() +  left_x;
    pixel_point.y = Map::Instance()->origin_y() +  left_y;
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);
    g_longitude = wgs_point.longitude;
    g_latitude = wgs_point.latitude;
    state->execute(&opera_context, EventReleaseLeft::Instance());
    assert(DoubleEqual(wgs_point.longitude,
                       DataStateRadar::Instance()->center_x()));
    assert(DoubleEqual(wgs_point.latitude,
                       DataStateRadar::Instance()->center_y()));
    return 0;
  }
};

void page(const char* str) {
  std::stringstream str_stream; 
  str_stream << "createRadar("
      << DataStateRadar::Instance()->id() << "," 
      << "0,"
      << g_longitude << ","
      << g_latitude << ","
      << "0);";
  assert(0 == strcmp(str, str_stream.str().c_str()));
}

} //namespace test
} //namespace tools

int main(){
  return tools::test::Test().RunAllTest();
}
