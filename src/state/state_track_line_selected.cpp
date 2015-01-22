#include "state/state_track_line_selected.h"

#include "data_state_line.h"
#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/data_track_unit_list.h"
#include "state/opera_context.h"
#include "state/state_internal_handle.h"
#include "state/state_track_line_started.h"
#include "util/tool.h"
#include "webkit/webkit.h"

namespace tools{
namespace{

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

void StateTrackLineSelected::execute(OperaContext* opera_context,
                                     Event* event) {
  if (IsEventInEditing(event)) {
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
      JSLine js_line = {
        DataStateLine::Instance()->id(),
        wgs_point.longitude,
        wgs_point.latitude,
        wgs_point.longitude,
        wgs_point.latitude
      };
      JSCreateLine js_create_line(&js_line);
      Webkit::Instance()->execute(js_create_line);
      opera_context->set_state(StateTrackLineStarted::Instance()); 
    } else if (IsEventInButtonLineCircleEclipse(event)) {
      StateSelectedEventHandle(opera_context, event);
    }
  }
}

StateTrackLineSelected* StateTrackLineSelected::Instance(){
  if (!state_) state_ = new StateTrackLineSelected();
  return state_;
}

StateTrackLineSelected* StateTrackLineSelected::state_ = 0;

} //namespace tools
