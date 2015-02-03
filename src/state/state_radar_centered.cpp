#include "state_radar_centered.h"

#include <math.h>

#include "event/event.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/opera_context.h"
#include "state/opera_option.h"
#include "state/data_state_radar.h"
#include "state/state_radar_selected.h"
#include "state/wheel_handle.h"
#include "webkit/webkit.h"

namespace tools {
namespace {

MapProjection::PixelPoint pixel_point;
MapProjection::WgsPoint wgs_point;

} //namespace

void StateRadarCentered::execute(OperaContext* opera_context, Event* event) {
  if (event == EventReleaseLeft::Instance()) {
    pixel_point.x = Map::Instance()->origin_x() 
        + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
        + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);
    
    double radius = sqrt(pow(wgs_point.longitude 
        - DataStateRadar::Instance()->center_x(), 2) 
        + pow(wgs_point.latitude - DataStateRadar::Instance()->center_y(), 2));

    JSRadar jsradar = {
      DataStateRadar::Instance()->id(),
      0,
      DataStateRadar::Instance()->center_x(),
      DataStateRadar::Instance()->center_y(),
      radius
    };
    
    JSUpdateRadar js_update_radar(&jsradar);
    Webkit::Instance()->execute(js_update_radar);
    
    OperaOption::Radar radar = {
      DataStateRadar::Instance()->id(),
      0,
      DataStateRadar::Instance()->center_x(),
      DataStateRadar::Instance()->center_y(),
      wgs_point.longitude,
      wgs_point.latitude
    };
    OperaOption::Instance()->push_back_radar(radar);
    opera_context->set_state(StateRadarSelected::Instance()); 
  } else if (event == EventReleaseRight::Instance()) {
    JSDeleteRadar js_delete_radar(DataStateRadar::Instance()->id());
    Webkit::Instance()->execute(js_delete_radar);
    opera_context->set_state(StateRadarSelected::Instance()); 
  } else if (event == EventMouseMove::Instance()) {
    pixel_point.x = Map::Instance()->origin_x() 
        + EventMouseMove::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
        + EventMouseMove::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
        ->FromPixelToWgs(pixel_point, wgs_point);
    
    double radius = sqrt(pow(wgs_point.longitude 
        - DataStateRadar::Instance()->center_x(), 2) 
        + pow(wgs_point.latitude - DataStateRadar::Instance()->center_y(), 2));
    JSRadar radar = {
      DataStateRadar::Instance()->id(),
      0,
      DataStateRadar::Instance()->center_x(),
      DataStateRadar::Instance()->center_y(),
      radius
    };
    JSUpdateRadar js_update_radar(&radar);
    Webkit::Instance()->execute(js_update_radar);
  } else {
    JSDeleteRadar js_delete_radar(DataStateRadar::Instance()->id());
    Webkit::Instance()->execute(js_delete_radar);
  }
}

StateRadarCentered* StateRadarCentered::Instance() {
  if (!state_) state_ = new StateRadarCentered();
  return state_;
}

StateRadarCentered* StateRadarCentered::state_ = 0;

} //namespace tools
