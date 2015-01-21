#include "state/state_radar_selected.h"

#include <assert.h>

#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/data_state_radar.h"
#include "state/opera_context.h"
#include "state/state_radar_centered.h"
#include "state/wheel_handle.h"
#include "util/tool.h"
#include "webkit/webkit.h"

namespace tools {
namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

void StateRadarSelected::execute(OperaContext* opera_context, Event* event) {
  if (event == EventReleaseLeft::Instance()) {
    pixel_point.x = Map::Instance()->origin_x() 
        + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
        + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);
    DataStateRadar::Instance()->set_id(GenerateId());
    DataStateRadar::Instance()->set_center(wgs_point.longitude, 
                                           wgs_point.latitude);
    JSRadar radar = {
      DataStateRadar::Instance()->id(),
      0,
      DataStateRadar::Instance()->center_x(),
      DataStateRadar::Instance()->center_y(),
      0
    };
    JSCreateRadar js_create_radar(&radar);
    Webkit::Instance()->execute(js_create_radar);
    opera_context->set_state(StateRadarCentered::Instance()); 
  }
}

StateRadarSelected* StateRadarSelected::Instance() {
  if (!state_) state_ = new StateRadarSelected();
  return state_;
}

StateRadarSelected* StateRadarSelected::state_ = 0;

} //namespace tools
