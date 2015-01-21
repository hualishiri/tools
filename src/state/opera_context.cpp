#include "opera_context.h"

#include "state/state.h"
#include "event/event.h"
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
    Webkit::Instance()->execute(js_set_zoom).execute(js_set_center);
  } else {
    state_->execute(this, event);
  }
}

} //namespace tools;
