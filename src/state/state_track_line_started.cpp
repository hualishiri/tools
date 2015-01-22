#include "state_track_line_started.h"

#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/data_state_line.h"
#include "state/data_track_unit_list.h"
#include "state/opera_context.h"
#include "state/opera_option.h"
#include "state/state_internal_handle.h"
#include "state/state_track_line_selected.h"
#include "util/tool.h"
#include "webkit/webkit.h"

namespace tools {
namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

void StateTrackLineStarted::execute(OperaContext* opera_context, Event* event) {
  opera_context_ = opera_context;
  if (IsEventInEditing(event)){
    if (event == EventReleaseLeft::Instance())
      EventReleaseLeftHandle();
    else if (event == EventReleaseRight::Instance())  
      EventReleaseRightHandle();
    else if (IsEventInButtonLineCircleEclipse(event))
      StateAfterSelectedEventHandle(opera_context, event);
  } else {
    EventReleaseRightHandle();
  }
}

StateTrackLineStarted* StateTrackLineStarted::Instance() {
  if (!state_) state_ = new StateTrackLineStarted();
  return state_;
}

void StateTrackLineStarted::EventReleaseLeftHandle() {
    pixel_point.x = Map::Instance()->origin_x()
        + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
        + EventReleaseLeft::Instance()->y();

    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);

    DataTrackUnitList::Instance()->push_back_line(
        DataStateLine::Instance()->id(),
        wgs_point.longitude,
        wgs_point.latitude );

    JSLine js_line = {
      DataStateLine::Instance()->id(),
      DataStateLine::Instance()->start_x(),
      DataStateLine::Instance()->start_y(),
      wgs_point.longitude,
      wgs_point.latitude
    };
    JSUpdateLine js_update_line(&js_line);
    Webkit::Instance()->execute(js_update_line);
    JSLine js_line_new = {
      GenerateId(),
      wgs_point.longitude,
      wgs_point.latitude,
      wgs_point.longitude,
      wgs_point.latitude
    };
    JSCreateLine js_create_line(&js_line_new);
    Webkit::Instance()->execute(js_create_line);

    SetDataLineCircleEclipse(GenerateId(),
                             wgs_point.longitude,
                             wgs_point.latitude);
}

void StateTrackLineStarted::EventReleaseRightHandle() {
    JSDeleteLine js_delete_line(DataStateLine::Instance()->id());
    Webkit::Instance()->execute(js_delete_line);
    if (!DataTrackUnitList::Instance()->empty()) {
      DataTrackUnitList::Instance()->set_id(GenerateId());
      OperaOption::Instance()
          ->push_back_track(DataTrackUnitList::Instance()->track());
      DataTrackUnitList::Instance()->clear();
    }
    opera_context_->set_state(StateTrackLineSelected::Instance());
}

void StateTrackLineStarted::EventMouseMoveHandle() {
    pixel_point.x = Map::Instance()->origin_x()
        + EventMouseMove::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
        + EventMouseMove::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs( pixel_point, wgs_point );
    DataStateLine::Instance()->set_move(wgs_point.longitude,
                                        wgs_point.latitude);
    JSLine line = { 
      DataStateLine::Instance()->id(),
      DataStateLine::Instance()->start_x(),
      DataStateLine::Instance()->start_y(),
      wgs_point.longitude,
      wgs_point.latitude
    };
    JSUpdateLine js_update_line(&line);
    Webkit::Instance()->execute(js_update_line);
}

void StateTrackLineStarted::EventOtherHandle() {
  EventReleaseRightHandle();
}

StateTrackLineStarted* StateTrackLineStarted::state_ = 0;

} //namespace tools
