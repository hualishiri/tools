#include "state.h"

#include <math.h>

#include <iostream>
#include <iomanip>

#include "event/event.h"
#include "webkit/webkit.h"
#include "map/map.h"
#include "map/map_projection.h"
#include "state/opera_option.h"
#include "util/tool.h"

namespace tools{
namespace {
MapProjection::WgsPoint wgs_point;
MapProjection::PixelPoint pixel_point;

void StateConvertSimple(State* state, Event* event){

}

void StateCovertComplex(State* state, Event* event){

}

/*void FromPixelToWgs( int x, int y ){
    pixel_point.x = Map::Instance()->origin_x() + x;
    pixel_point.y = Map::Instance()->origin_y() + y;
    MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);
}*/

/*void FromWgsToPixel(){
  MapProjection::Instance(Map::Instance()->zoom())
    ->FromWgsToPixel(wgs_point, pixel_point);
}

void FromPixelToWgs(){
  MapProjection::Instance(Map::Instance()->zoom())
    ->FromPixelToWgs(pixel_point, wgs_point);
}*/

void EventWheelHandle(int angle, int x, int y){
    int delta = angle / 120;
    int new_zoom = Map::Instance()->zoom() + delta;
    if( new_zoom <4 || new_zoom > 16)
      return;
    pixel_point.x = Map::Instance()->origin_x() + x;
    pixel_point.y = Map::Instance()->origin_y() + y;
    MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);

    Map::Instance()->set_zoom(new_zoom);

    MapProjection::Instance(Map::Instance()->zoom())
      ->FromWgsToPixel(wgs_point, pixel_point);

    Map::Instance()->set_origin_x(pixel_point.x - x);
    Map::Instance()->set_origin_y(pixel_point.y - y);

    pixel_point.x = Map::Instance()->center_x();
    pixel_point.y = Map::Instance()->center_y();

    MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);

    std::cout << "setZoom(" << new_zoom << ")" << std::endl;
    std::cout << "setCenter(" << wgs_point.longitude << ","
      << wgs_point.latitude << ");";
}

} //namespace

void ToolsState::Execute(Event* event){ 
  state_->execute(this, event); 
}

State::~State(){}

StateRadarSelected* StateRadarSelected::state_ = 0;
StateRadarCentered* StateRadarCentered::state_ = 0;

StateTrackLineSelected* StateTrackLineSelected::state_ = 0;
StateTrackLineStarted* StateTrackLineStarted::state_ = 0;

StateTrackCircleSelected* StateTrackCircleSelected::state_ = 0;
StateTrackCircleStarted* StateTrackCircleStarted::state_ = 0;
StateTrackCircleCentered* StateTrackCircleCentered::state_ = 0;
StateTrackCircleSided* StateTrackCircleSided::state_ = 0;

StateTrackEclipseSelected* StateTrackEclipseSelected::state_ = 0;
StateTrackEclipseStarted* StateTrackEclipseStarted::state_ = 0;
StateTrackEclipseCentered* StateTrackEclipseCentered::state_ = 0;
StateTrackEclipseEnded* StateTrackEclipseEnded::state_ = 0;
StateTrackEclipseSided* StateTrackEclipseSided::state_ = 0;

StateContralStarted* StateContralStarted::state_ = 0;
StateContralSteped* StateContralSteped::state_ = 0;
StateContralPaused* StateContralPaused::state_ = 0;

StateRadarSelected* StateRadarSelected::Instance(){
  if(!state_) state_ = new StateRadarSelected();
  return state_;
}

StateRadarCentered* StateRadarCentered::Instance(){
  if(!state_) state_ = new StateRadarCentered();
  return state_;
}

StateTrackLineSelected* StateTrackLineSelected::Instance(){
  if(!state_) state_ = new StateTrackLineSelected();
  return state_;
}

StateTrackLineStarted* StateTrackLineStarted::Instance(){
  if(!state_) state_ = new StateTrackLineStarted();
  return state_;
}

StateTrackCircleSelected* StateTrackCircleSelected::Instance(){
  if(!state_) state_ = new StateTrackCircleSelected();
  return state_;
}

StateTrackCircleStarted* StateTrackCircleStarted::Instance(){
  if(!state_) state_ = new StateTrackCircleStarted();
  return state_;
}

StateTrackCircleCentered* StateTrackCircleCentered::Instance(){
  if(!state_) state_ = new StateTrackCircleCentered();
  return state_;
}

StateTrackCircleSided* StateTrackCircleSided::Instance(){
  if(!state_) state_ = new StateTrackCircleSided();
  return state_;
}

StateTrackEclipseSelected* StateTrackEclipseSelected::Instance(){
  if(!state_) state_ = new StateTrackEclipseSelected();
  return state_;
}

StateTrackEclipseStarted* StateTrackEclipseStarted::Instance(){
  if(!state_) state_ = new StateTrackEclipseStarted();
  return state_;
}

StateTrackEclipseCentered* StateTrackEclipseCentered::Instance(){
  if(!state_) state_ = new StateTrackEclipseCentered();
  return state_;
}

StateTrackEclipseEnded* StateTrackEclipseEnded::Instance(){
  if(!state_) state_ = new StateTrackEclipseEnded();
  return state_;
}

StateTrackEclipseSided* StateTrackEclipseSided::Instance(){
  if(!state_) state_ = new StateTrackEclipseSided();
  return state_;
}

StateContralStarted* StateContralStarted::Instance(){
  if(!state_) state_ = new StateContralStarted();
  return state_;
}

StateContralSteped* StateContralSteped::Instance(){
  if(!state_) state_ = new StateContralSteped();
  return state_;
}

StateContralPaused* StateContralPaused::Instance(){
  if(!state_) state_ = new StateContralPaused();
  return state_;
}

void StateRadarSelected::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    pixel_point.x = Map::Instance()->origin_x() 
      + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
      + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);
    std::cout << wgs_point.longitude << " "
      << wgs_point.latitude << std::endl;

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

    tools_state->set_state(StateRadarCentered::Instance()); 
    return;
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    return;
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
  }
}

void StateRadarCentered::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    pixel_point.x = Map::Instance()->origin_x() 
      + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
      + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);
    
    double radius = sqrt(pow(wgs_point.longitude - 
      DataStateRadar::Instance()->center_x(), 2) 
      + pow(wgs_point.latitude - 
      DataStateRadar::Instance()->center_y(), 2));   

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

    //OperaOption::Instance()->push_back_radar(radar);

    tools_state->set_state(StateRadarSelected::Instance()); 
    return;
  }
  if(event == EventReleaseRight::Instance()){
    std::cout << "deleteRadar("
      << DataStateRadar::Instance()->id()
      << ");" << std::endl;
    tools_state->set_state(StateRadarSelected::Instance()); 
    return;
  }
  if(event == EventMouseMove::Instance()){
    pixel_point.x = Map::Instance()->origin_x() 
      + EventReleaseLeft::Instance()->x();
    pixel_point.y = Map::Instance()->origin_y()
      + EventReleaseLeft::Instance()->y();
    MapProjection::Instance(Map::Instance()->zoom())
      ->FromPixelToWgs(pixel_point, wgs_point);
    
    double radius = sqrt(pow(wgs_point.longitude - 
      DataStateRadar::Instance()->center_x(), 2) 
      + pow(wgs_point.latitude - 
      DataStateRadar::Instance()->center_y(), 2));   

      DataStateRadar::Instance()->set_move(
        EventMouseMove::Instance()->x(),
        EventMouseMove::Instance()->y());

    std::cout << "[IN]updateRadar("
      << DataStateRadar::Instance()->id() << ","
      << DataStateRadar::Instance()->center_x() << ","
      << DataStateRadar::Instance()->center_y() << ","
      << 0 << ");" << std::endl;
    return;
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    return;
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
  }
  std::cout << "deleteRadar(" << DataStateRadar::Instance()->id() << ");";
}

void StateTrackLineSelected::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataTrackUnitList::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
      DataStateLine::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    tools_state->set_state(StateTrackLineStarted::Instance()); 
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
  }
}
void StateTrackLineStarted::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateLine::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    DataTrackUnitList::Instance()->push_back_line(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    tools_state->set_state(StateTrackLineSelected::Instance()); 
    return;
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    return;
  }
  if(event == EventMouseMove::Instance()){
    DataStateLine::Instance()->set_move(
      EventMouseMove::Instance()->x(),
      EventMouseMove::Instance()->y());
    std::cout << "[IN]updateLine(id, x, y, x1, y1);" << std::endl;
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}

void StateTrackCircleSelected::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateCircle::Instance()->circle_.start_x = EventReleaseLeft::Instance()->x();
    DataStateCircle::Instance()->circle_.start_y = EventReleaseLeft::Instance()->y();
    DataTrackUnitList::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    tools_state->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
  }
}
void StateTrackCircleStarted::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateCircle::Instance()->circle_.center_x = EventReleaseLeft::Instance()->x();
    DataStateCircle::Instance()->circle_.center_y = EventReleaseLeft::Instance()->y();
    std::cout << "Draw a Circle" << std::endl;
    tools_state->set_state(StateTrackCircleCentered::Instance());
    return;
  }
  if(event == EventReleaseRight::Instance()
    && DataTrackUnitList::Instance()->empty())
    tools_state->set_state(StateTrackCircleSelected::Instance());
  if(event == EventMouseMove::Instance()){
    DataStateCircle::Instance()->move_.x = EventReleaseLeft::Instance()->x();
    DataStateCircle::Instance()->move_.y = EventReleaseLeft::Instance()->y();
    std::cout << "Dynamic Draw a circle" << std::endl;
    return;
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackCircleCentered::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateCircle::Instance()->circle_.side_x = EventReleaseLeft::Instance()->x();
    DataStateCircle::Instance()->circle_.side_y = EventReleaseLeft::Instance()->y();
    std::cout << "upDateCircle();" << std::endl;
    tools_state->set_state(StateTrackCircleSided::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackCircleSided::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataTrackUnitList::Instance()->push_back_circle(
      DataStateCircle::Instance()->circle_.center_x,
      DataStateCircle::Instance()->circle_.center_y,
      DataStateCircle::Instance()->circle_.side_x,
      DataStateCircle::Instance()->circle_.side_y,
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y()
    );
    DataStateCircle::Instance()->circle_.start_x = EventReleaseLeft::Instance()->x();
    DataStateCircle::Instance()->circle_.start_y = EventReleaseLeft::Instance()->y();
    tools_state->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}

void StateTrackEclipseSelected::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.start_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.start_y = EventReleaseLeft::Instance()->y();
    DataTrackUnitList::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y()
    );
    tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
  }
}

void StateTrackEclipseStarted::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.center_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.center_y = EventReleaseLeft::Instance()->y();
    tools_state->set_state(StateTrackEclipseCentered::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackEclipseCentered::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.end_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.end_y = EventReleaseLeft::Instance()->y();
    tools_state->set_state(StateTrackEclipseEnded::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackEclipseEnded::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.side_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.side_y = EventReleaseLeft::Instance()->y();
    tools_state->set_state(StateTrackEclipseSided::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackEclipseSided::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.angle_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.angle_y = EventReleaseLeft::Instance()->y();
    DataTrackUnitList::Instance()->push_back_eclipse(
      DataStateEclipse::Instance()->eclipse_.center_x,    
      DataStateEclipse::Instance()->eclipse_.center_y,    
      DataStateEclipse::Instance()->eclipse_.end_x,    
      DataStateEclipse::Instance()->eclipse_.end_y,    
      DataStateEclipse::Instance()->eclipse_.side_x,    
      DataStateEclipse::Instance()->eclipse_.side_y,    
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y()
    );
    tools_state->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    EventWheelHandle(EventWheel::Instance()->angle(),
      EventWheel::Instance()->x(), EventWheel::Instance()->y());
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackEclipseSelected::Instance());
    else
      tools_state->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
  
}

void StateContralStarted::execute(ToolsState* tools_state, Event* event){

}
void StateContralSteped::execute(ToolsState* tools_state, Event* event){
  
}
void StateContralPaused::execute(ToolsState* tools_state, Event* event){

}

DataStateRadar* DataStateRadar::data_ = 0;
DataStateLine* DataStateLine::data_ = 0;
DataStateCircle* DataStateCircle::data_ = 0;
DataStateEclipse* DataStateEclipse::data_ = 0;
DataRadarList* DataRadarList::radar_list_ = 0;

DataStateRadar* DataStateRadar::Instance(){
  if(!data_) data_ = new DataStateRadar();
  return data_;
}

DataStateLine* DataStateLine::Instance(){
  if(!data_) data_ = new DataStateLine();
  return data_;
}

DataStateCircle* DataStateCircle::Instance(){
  if(!data_) data_ = new DataStateCircle();
  return data_;
}

DataStateEclipse* DataStateEclipse::Instance(){
  if(!data_) data_ = new DataStateEclipse();
  return data_;
}

DataRadarList* DataRadarList::Instance(){
  if(!radar_list_) radar_list_ = new DataRadarList();
  return radar_list_;
}

DataTrackUnitList* DataTrackUnitList::data_ = 0;
DataTrackUnitList* DataTrackUnitList::Instance(){
  if(!data_) data_ = new DataTrackUnitList();
  return data_;
}

void DataTrackUnitList::push_back_line(double end_x, double end_y){
  units_flag_.push_back(LINE);
  units_.push_back(end_x);
  units_.push_back(end_y);
}

void DataTrackUnitList::push_back_circle(double center_x, double center_y,
    double side_x, double side_y, double angle_x, double angle_y){
  units_flag_.push_back(CIRCLE);
  units_.push_back(center_x);
  units_.push_back(center_y);
  units_.push_back(side_x);
  units_.push_back(side_y);
  units_.push_back(angle_x);
  units_.push_back(angle_y);
}

void DataTrackUnitList::push_back_eclipse(double center_x, double center_y,
    double end_x, double end_y,
    double side_x, double side_y,
    double angle_x, double angle_y){
  units_flag_.push_back(ECLIPSE);
  units_.push_back(center_x);
  units_.push_back(center_y);
  units_.push_back(end_x);
  units_.push_back(end_y);
  units_.push_back(side_x);
  units_.push_back(side_y);
  units_.push_back(angle_x);
  units_.push_back(angle_y);
}

} //namespace tools
