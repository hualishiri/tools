#include "state.h"

#include <iostream>

#include "event/event.h"
#include "util/tool.h"

namespace tools{
namespace {

void StateConvertSimple(State* state, Event* event){

}

void StateCovertComplex(State* state, Event* event){

}

}
void ToolsState::Execute(Event* event){ 
  state_->execute(this, event); 
//  if(event == EventButtonRadar::Instance()
 //   ){}
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
    DataStateRadar::Instance()->set_id(GenerateId());
    DataStateRadar::Instance()->set_center(EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    std::cout << "[IN]createRadar("
      << DataStateRadar::Instance()->id() << ","
      << DataStateRadar::Instance()->center_x() << ","
      << DataStateRadar::Instance()->center_y() << ","
      << 0 << ");" << std::endl;
    tools_state->set_state(StateRadarCentered::Instance()); 
    return;
  }
  if(event == EventWheel::Instance()){
    //TODO: something
    return;
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
    return;
  }
}

void StateRadarCentered::execute(ToolsState* tools_state, Event* event){
  if(event == EventReleaseLeft::Instance()){
      std::cout << "[IN]updateRadar(id, x, y,type, radius);." << std::endl;
      DataRadarList::Instance()->push_back_radar(
          DataStateRadar::Instance()->center_x(),
          DataStateRadar::Instance()->center_y(),
          EventPressLeft::Instance()->x(),
          EventPressLeft::Instance()->y()
        );
    std::cout << "[IN]Create Radar Object" << std::endl;
    tools_state->set_state(StateRadarSelected::Instance()); 
    return;
  }
  if(event == EventReleaseRight::Instance()){
    std::cout << "deleteRadar(id);" << std::endl;
    tools_state->set_state(StateRadarSelected::Instance()); 
    return;
  }
  if(event == EventMouseMove::Instance()){
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
    //TODO: something
    return;
  }
  if(event == EventButtonLine::Instance()){
    tools_state->set_state(StateTrackLineSelected::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    tools_state->set_state(StateTrackCircleSelected::Instance());
      return;
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
    return;
  }
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

void DataTrackUnitList::push_back_line(int end_x, int end_y){
  units_flag_.push_back(LINE);
  units_.push_back(end_x);
  units_.push_back(end_y);
}

void DataTrackUnitList::push_back_circle(int center_x, int center_y,
    int side_x, int side_y, int angle_x, int angle_y){
  units_flag_.push_back(CIRCLE);
  units_.push_back(center_x);
  units_.push_back(center_y);
  units_.push_back(side_x);
  units_.push_back(side_y);
  units_.push_back(angle_x);
  units_.push_back(angle_y);
}

void DataTrackUnitList::push_back_eclipse(int center_x, int center_y,
    int end_x, int end_y,
    int side_x, int side_y,
    int angle_x, int angle_y){
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
