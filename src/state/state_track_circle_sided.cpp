#include "state_track_circle_sided.h"

#include <math.h>

#include "event/event.h"
#include "webkit/webkit.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/data_state_circle.h"
#include "state/data_track_unit_list.h"
#include "state/opera_context.h"
#include "state/opera_option.h"
#include "state/state_internal_handle.h"
#include "state/state_track_circle_started.h"
#include "util/tool.h"

namespace tools {

extern const double T_PI;

namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

StateTrackCircleSided* StateTrackCircleSided::Instance() {
  if (!state_) state_ = new StateTrackCircleSided();
  return state_;
}

void StateTrackCircleSided::execute(OperaContext* opera_context, Event* event) {
  if (IsEventInEditing(event)) {
    if (event == EventReleaseLeft::Instance()) { 
      pixel_point.x = Map::Instance()->origin_x()
          + EventReleaseLeft::Instance()->x();
      pixel_point.y = Map::Instance()->origin_y()
          + EventReleaseLeft::Instance()->y();
      MapProjection::Instance(Map::Instance()->zoom())->FromPixelToWgs(
          pixel_point, wgs_point);
      DataTrackUnitList::Instance()->push_back_circle(
          DataStateCircle::Instance()->circle_.id,
          DataStateCircle::Instance()->circle_.center_x,
          DataStateCircle::Instance()->circle_.center_y,
          DataStateCircle::Instance()->circle_.side_x,
          DataStateCircle::Instance()->circle_.side_y,
          wgs_point.longitude,
          wgs_point.latitude);
      double angle = AngleFromStartByClockInCircle(
          DataStateCircle::Instance()->circle_.start_x,
          DataStateCircle::Instance()->circle_.start_y,
          DataStateCircle::Instance()->circle_.center_x,
          DataStateCircle::Instance()->circle_.center_y,
          DataStateCircle::Instance()->circle_.side_x,
          DataStateCircle::Instance()->circle_.side_y);
      JSCircle js_circle = {
        DataStateCircle::Instance()->circle_.id,
        DataStateCircle::Instance()->circle_.start_x,
        DataStateCircle::Instance()->circle_.start_y,
        DataStateCircle::Instance()->circle_.center_x,
        DataStateCircle::Instance()->circle_.center_y,
        DataStateCircle::Instance()->circle_.direction * angle
      };
      JSUpdateCircle js_update_circle(&js_circle);
      Webkit::Instance()->execute(js_update_circle);
      double angle_std = AngleInCircle(
          DataStateCircle::Instance()->circle_.side_x
          - DataStateCircle::Instance()->circle_.center_x,
          DataStateCircle::Instance()->circle_.side_y
          - DataStateCircle::Instance()->circle_.center_y);
      double radius = sqrt(pow(DataStateCircle::Instance()->circle_.start_x 
          - DataStateCircle::Instance()->circle_.center_x ,2) 
          + pow(DataStateCircle::Instance()->circle_.start_y 
          - DataStateCircle::Instance()->circle_.center_y, 2));
      double x0 = DataStateCircle::Instance()->circle_.center_x 
          + radius * cos(angle_std);
      double y0 = DataStateCircle::Instance()->circle_.center_y 
          + radius * sin(angle_std);
      SetDataLineCircleEclipse(GenerateId(), x0, y0);
      JSCircle js_circle_new = {
        DataStateCircle::Instance()->circle_. id,
        x0,
        y0,
        x0,
        y0,
        2 * T_PI
      };
      JSCreateCircle js_create_circle(&js_circle_new);
      Webkit::Instance()->execute(js_create_circle);
      opera_context->set_state(StateTrackCircleStarted::Instance());
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

StateTrackCircleSided* StateTrackCircleSided::state_ = 0;

} //namespace tools
