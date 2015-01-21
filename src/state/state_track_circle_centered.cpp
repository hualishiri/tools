#include "state_track_circle_centered.h"

#include <assert.h>
#include <math.h>

#include "event/event.h"
#include "webkit/webkit.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "webkit/webkit.h"
#include "state/data_state_circle.h"
#include "state/state_internal_handle.h"
#include "state/opera_context.h"
#include "state/state_track_circle_selected.h"
#include "state/state_track_circle_sided.h"
#include "util/tool.h"

namespace tools {
namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

int Side(double start_x,
         double start_y,
         double center_x,
         double center_y,
         double side_x,
         double side_y) {
  double delta = AngleInCircle(side_x - start_x, side_y - start_y) 
      - AngleInCircle(center_x - start_x, center_y - start_y);
  if (delta > 0 && delta < M_PI)
    return 1;
  return -1;
}

} //namespace

StateTrackCircleCentered* StateTrackCircleCentered::Instance() {
  if (!state_) state_ = new StateTrackCircleCentered();
  return state_;
}

void StateTrackCircleCentered::execute(OperaContext* opera_context,
    Event* event) {
  if (IsEventInEditing(event)) {
    if (event == EventReleaseLeft::Instance()) {
      pixel_point.x = Map::Instance()->origin_x() 
          + EventReleaseLeft::Instance()->x();
      pixel_point.y = Map::Instance()->origin_y()
          + EventReleaseLeft::Instance()->y();
      MapProjection::Instance(Map::Instance()->zoom())
          ->FromPixelToWgs(pixel_point, wgs_point);
      DataStateCircle::Instance()->circle_.side_x = wgs_point.longitude;
      DataStateCircle::Instance()->circle_.side_y = wgs_point.latitude;
      int direction = Side(
          DataStateCircle::Instance()->circle_.start_x,
          DataStateCircle::Instance()->circle_.start_y,
          DataStateCircle::Instance()->circle_.center_x,
          DataStateCircle::Instance()->circle_.center_y,
          wgs_point.longitude,
          wgs_point.latitude);
      DataStateCircle::Instance()->circle_.direction = direction;
      JSCircle js_circle = {
        DataStateCircle::Instance()->circle_.id,
        DataStateCircle::Instance()->circle_.start_x,
        DataStateCircle::Instance()->circle_.start_y,
        DataStateCircle::Instance()->circle_.center_x,
        DataStateCircle::Instance()->circle_.center_y,
        direction * M_PI
      };
      JSUpdateCircle js_update_circle(&js_circle);
      Webkit::Instance()->execute(js_update_circle);
      opera_context->set_state(StateTrackCircleSided::Instance());
    } else if (event == EventReleaseRight::Instance()) {
      StateCircleEventReleaseRightHandle(
          DataStateCircle::Instance()->circle_.id, opera_context);
    } else if (event == EventMouseMove::Instance()) {
      //TODO: something
    } else if (IsEventInButtonLineCircleEclipse(event)) {
      StateAfterSelectedEventHandle(opera_context, event);
    }
  } else {
    StateCircleEventReleaseRightHandle(
        DataStateCircle::Instance()->circle_.id, opera_context);
  }
}

StateTrackCircleCentered* StateTrackCircleCentered::state_ = 0;

} //namespace tools
