#include "state_track_circle_sided.h"

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
      SetDataLineCircleEclipse(GenerateId(),
                               wgs_point.longitude,
                               wgs_point.latitude);
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
