#include "state_track_circle_started.h"

#include <math.h>

#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "webkit/webkit.h"
#include "state/data_state_circle.h"
#include "state/opera_context.h"
#include "state/state_track_circle_selected.h"
#include "state/state_track_circle_started.h"
#include "state/state_track_circle_centered.h"
#include "state/state_internal_handle.h"

namespace tools {

namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

StateTrackCircleStarted* StateTrackCircleStarted::Instance() {
  if (!state_) state_ = new StateTrackCircleStarted();
  return state_;
}

void StateTrackCircleStarted::execute(OperaContext* opera_context, 
                                      Event* event){
  if (IsEventInEditing(event)) {
    if (event == EventReleaseLeft::Instance()) {
      pixel_point.x = Map::Instance()->origin_x() 
          + EventReleaseLeft::Instance()->x();
      pixel_point.y = Map::Instance()->origin_y() 
          + EventReleaseLeft::Instance()->y();
      MapProjection::Instance(Map::Instance()->zoom())
          ->FromPixelToWgs(pixel_point, wgs_point);
      DataStateCircle::Instance()->circle_.center_x 
          = wgs_point.longitude;
      DataStateCircle::Instance()->circle_.center_y
          = wgs_point.latitude;
      JSCircle js_circle = {
        DataStateCircle::Instance()->circle_.id,
        DataStateCircle::Instance()->circle_.start_x,
        DataStateCircle::Instance()->circle_.start_y,
        DataStateCircle::Instance()->circle_.center_x,
        DataStateCircle::Instance()->circle_.center_y,
        2*M_PI 
      };
      JSUpdateCircle js_update_circle(&js_circle);
      Webkit::Instance()->execute(js_update_circle);
      opera_context->set_state(StateTrackCircleCentered::Instance());
    } else if (event == EventReleaseRight::Instance()) {
      StateCircleEventReleaseRightHandle(
          DataStateCircle::Instance()->circle_.id,
          opera_context);
    } else if (event == EventMouseMove::Instance()){
      //TODO: something
    } else if (IsEventInButtonLineCircleEclipse(event)) {
      StateAfterSelectedEventHandle(opera_context, event);
    }
  } else {
    StateCircleEventReleaseRightHandle(
        DataStateCircle::Instance()->circle_.id,
        opera_context);
  }
}

StateTrackCircleStarted* StateTrackCircleStarted::state_ = 0;

} //namespace tools
