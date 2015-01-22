#define private public

#include "state_track_line_started.h"

#include <assert.h>

#include <iostream>
#include <sstream>

#include "event/event.h"
#include "webkit/webkit.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/data_state_line.h"
#include "state/data_state_circle.h"
#include "state/data_track_unit_list.h"
#include "state/opera_context.h"
#include "state/state_track_line_selected.h"
#include "state/state_track_line_started.h"
#include "state/state_track_circle_selected.h"
#include "util/tool.h"


namespace tools {
namespace test {
char std_str[10][100];
int index = 0;

void page(const char* str);
void InitEnv(int zoom,
             int origin_x,
             int origin_y,
             int width,
             int height,
             void (*fun)(const char*));

class Test {
 public:
  int RunAllTest() {
    int sum = 0;
    sum += TestEventReleaseLeft();
    sum += TestEventReleaseRight();
    sum += TestEventButtonCircle();
    return sum;
  }
  int TestEventReleaseLeft() {
    InitEnv(10, 67247, 97459, 1080, 300, page);
    OperaContext opera_context(StateTrackLineSelected::Instance());
    EventReleaseLeft::Instance()->set(40, 40);

    MapProjection::PixelPoint pixel_point;
    MapProjection::WgsPoint wgs_point;
    pixel_point.x = Map::Instance()->origin_x() 
        + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y() 
        + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);

    std::stringstream str_stream;
    str_stream << "createLine("
      << GenerateId() + 1 << ","
      << wgs_point.longitude << ","
      << wgs_point.latitude << ","
      << wgs_point.longitude << ","
      << wgs_point.latitude << ");";
    strcpy(std_str[0], str_stream.str().c_str());
    opera_context.Execute(EventReleaseLeft::Instance());

    EventReleaseLeft::Instance()->set(80, 80);

    pixel_point.x = Map::Instance()->origin_x() 
        + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y() 
        + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);

    std::stringstream str_stream_right;
    str_stream_right << "updateLine("
      << DataStateLine::Instance()->id() << ","
      << DataStateLine::Instance()->start_x() << ","
      << DataStateLine::Instance()->start_y() << ","
      << wgs_point.longitude << ","
      << wgs_point.latitude << ");";
    strcpy(std_str[1], str_stream_right.str().c_str());

    std::stringstream str_stream_right_create;
    str_stream_right_create << "createLine("
      << DataStateLine::Instance()->id() + 1 << ","
      << wgs_point.longitude  << ","
      << wgs_point.latitude << ","
      << wgs_point.longitude << ","
      << wgs_point.latitude << ");";
    strcpy(std_str[2], str_stream_right_create.str().c_str());

    
    opera_context.Execute(EventReleaseLeft::Instance());
    
    assert(opera_context.state() == StateTrackLineStarted::Instance());

    assert(DoubleEqual(DataStateLine::Instance()->start_x(),
                       wgs_point.longitude));
    assert(DoubleEqual(DataStateLine::Instance()->start_y(),
                       wgs_point.latitude));
    assert(DoubleEqual(DataStateCircle::Instance()->circle_.start_x,
                       wgs_point.longitude));
    assert(DoubleEqual(DataStateCircle::Instance()->circle_.start_y,
                       wgs_point.latitude));
    
    return 0;
  }

  int TestEventReleaseRight() {
    InitEnv(10, 67247, 97459, 1080, 300, page);
    OperaContext opera_context(StateTrackLineSelected::Instance());
    index = 0;
    SetId(0x0bef0);
    EventReleaseLeft::Instance()->set(40, 40);
    opera_context.Execute(EventReleaseLeft::Instance());
    

    index = 3;
    std::stringstream str_stream_right_create;
    str_stream_right_create << "deleteLine("
      << DataStateLine::Instance()->id() << ");";
    strcpy(std_str[3], str_stream_right_create.str().c_str());

    EventReleaseRight::Instance()->set(40, 40);
    opera_context.Execute(EventReleaseRight::Instance());

    assert(opera_context.state() == StateTrackLineSelected::Instance());
    return 0;
  }

  int TestEventButtonCircle(){
    InitEnv(10, 67247, 97459, 1080, 300, page);
    OperaContext opera_context(StateTrackLineSelected::Instance());
    index = 0;
    SetId(0x0bef0);
    EventReleaseLeft::Instance()->set(40, 40);
    opera_context.Execute(EventReleaseLeft::Instance());
    
    opera_context.Execute(EventButtonCircle::Instance());
    assert(opera_context.state() == StateTrackCircleSelected::Instance());
    return 0;
  }
};

void page(const char* str) {
  std::cout << std_str[index] << std::endl;
  std::cout << str << std::endl;
  assert(0 == strcmp(std_str[index], str));
  index++;
}

void InitEnv(int zoom,
             int origin_x,
             int origin_y,
             int width,
             int height,
             void(*fun)(const char*)) {
  Map::Instance()->set_zoom(zoom);
  Map::Instance()->set_origin_x(origin_x);
  Map::Instance()->set_origin_y(origin_y);
  Map::Instance()->set_width(width);
  Map::Instance()->set_height(height);
  Webkit::Instance()->set_page(fun);
}

} //namespace test
} //namespace tools

int main() {
  return tools::test::Test().RunAllTest();
}
