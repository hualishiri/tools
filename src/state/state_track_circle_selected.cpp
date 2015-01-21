#include "state_track_circle_selected.h"

#include <math.h>

#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "webkit/webkit.h"
#include "state/data_state_circle.h"
#include "state/data_track_unit_list.h"
#include "state/opera_context.h"
#include "state/state_internal_handle.h"
#include "state/state_track_circle_started.h"
#include "util/tool.h"

namespace tools {

namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

StateTrackCircleSelected* StateTrackCircleSelected::Instance() {
  if (!state_) state_ = new StateTrackCircleSelected();
  return state_;
}

void StateTrackCircleSelected::execute(OperaContext* opera_context,
                                       Event* event) {
  if (IsEventInEditing(event)){
    if (event == EventReleaseLeft::Instance()) {
      pixel_point.x = Map::Instance()->origin_x()
          + EventReleaseLeft::Instance()->x();
      pixel_point.y = Map::Instance()->origin_y()
          + EventReleaseLeft::Instance()->y();
      MapProjection::Instance(Map::Instance()->zoom())
          ->FromPixelToWgs(pixel_point, wgs_point);
  
      DataTrackUnitList::Instance()->set_start(wgs_point.longitude,
                                               wgs_point.latitude);
      SetDataLineCircleEclipse(GenerateId(),
                               wgs_point.longitude,
                               wgs_point.latitude);
      JSCircle js_circle = {
        GenerateId(),
        wgs_point.longitude,
        wgs_point.latitude,
        wgs_point.longitude,
        wgs_point.latitude,
        2*M_PI 
      };
      JSCreateCircle js_create_circle(&js_circle);
      Webkit::Instance()->execute(js_create_circle);
      opera_context->set_state(StateTrackCircleStarted::Instance());
    } else if (IsEventInButtonLineCircleEclipse(event)) {
      StateSelectedEventHandle(opera_context, event);
    }
  }
}

StateTrackCircleSelected* StateTrackCircleSelected::state_ = 0;

} //namespace tools
