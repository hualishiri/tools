#include "opera_context.h"

#include <iostream>

#include "state/state.h"
#include "event/event.h"
#include "map/map.h"
#include "webkit/webkit.h"
#include "state/wheel_handle.h"

namespace tools {

void OperaContext::Execute(Event* event) {
  if (event == EventWheel::Instance()) {
    WheelHandle wheel_handle(EventWheel::Instance()->angle(),
                             EventWheel::Instance()->x(),
                             EventWheel::Instance()->y());
    JSSetZoom js_set_zoom(wheel_handle.map_zoom());
    JSSetCenter js_set_center(wheel_handle.map_center_longitude(),
                              wheel_handle.map_center_latitude());
    Map::Instance()->set_zoom(wheel_handle.map_zoom());
    Map::Instance()->set_origin_x(wheel_handle.map_origin_x());
    Map::Instance()->set_origin_y(wheel_handle.map_origin_y());
    Webkit::Instance()->execute(js_set_zoom).execute(js_set_center);
    std::cout << "map: zoom: " << Map::Instance()->zoom() << std::endl
        << "map: origin_x: " << Map::Instance()->origin_x() << std::endl
        << "map: origin_y: " << Map::Instance()->origin_y() << std::endl
        << "map: width: " << Map::Instance()->width() << std::endl
        << "map: height: " << Map::Instance()->height() << std::endl;
  } else {
    state_->execute(this, event);
  }
}

} //namespace tools;
