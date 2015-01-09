#include "state.h"

#include <iostream>

namespace tools{

void ToolsState::Execute(Event* event){ state_->execute(this, event); }
bool ToolsState::IsFirstTrackUnit() const{
    if(stack_[0] == StateTrackLineSelected::Instance()
      && stack_.size() < 3)
      return false;
    if(stack_[0] == StateTrackCircleSelected::Instance()
      && stack_.size() < 4)
      return false;
    if(stack_[0] == StateTrackEclipseSelected::Instance()
      && stack_.size() < 5)
      return false;
    return true;
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
    std::cout << "[IN]createRadar(id,x,y,type, radius);." << std::endl;
    DataStateRadar::Instance()->set_center(EventReleaseLeft::Instance()->x(),
        EventReleaseLeft::Instance()->y());
    tools_state->set_state(StateRadarCentered::Instance()); 
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
  /*switch (event){
    case EventReleaseLeft::Instance():
      std::cout << "[OUT]put MOUSE_RELEASE_LEFT position to stack" << std::endl;
      std::cout << "[IN]createRadar(id,x,y,type, radius);." << std::endl;
      std::cout << "[IN]put current state to stack." << std::endl;
      std::cout << "[IN][StateRadarSelected]->[StateRadarCentered]" << std::endl;
      tools_state->push_back(this);
      tools_state->set_state(StateRadarCentered::Instance()); 
      break;
    case BUTTON_LINE :
      std::cout << "[IN][StateRadarSelected]->[StateTrackLineSelected]" << std::endl;
      tools_state->set_state(StateTrackLineSelected::Instance());
      break;
    case BUTTON_CIRCLE :
      std::cout << "[IN][StateRadarSelected]->[StateTrackCircleSelected]" << std::endl;
      tools_state->set_state(StateTrackCircleSelected::Instance());
      break;
    case BUTTON_ECLIPSE:
      std::cout << "[IN][StateRadarSelected]->[StateTrackEclipseSelected]" << std::endl;
      tools_state->set_state(StateTrackEclipseSelected::Instance());
      break;
    default:
      std::cout << "[IN]No Response Event" << std::endl;
  }*/
}


void StateRadarCentered::execute(ToolsState* tools_state, Event* event){
  if(event == EventPressLeft::Instance()){
      std::cout << "[IN]updateRadar(id, x, y,type, radius);." << std::endl;
      DataRadarList::Instance()->push_back_radar(
          DataStateRadar::Instance()->center_x(),
          DataStateRadar::Instance()->center_y(),
          EventPressLeft::Instance()->x(),
          EventPressLeft::Instance()->y()
        );
      std::cout << "[IN]Create Radar Object" << std::endl;
      tools_state->set_state(StateRadarSelected::Instance()); 
  }
  if(event == EventPressRight::Instance()){
    tools_state->set_state(StateRadarSelected::Instance()); 
  }
  if(event == EventMouseMove::Instance()){
      DataStateRadar::Instance()->set_move(
        EventMouseMove::Instance()->x(),
        EventMouseMove::Instance()->y());
      std::cout << "[IN]updateRadar(id, x, y, type, radius);" << std::endl;
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

  /*switch (action){
    case MOUSE_RELEASE_LEFT :
      std::cout << "[OUT]put MOUSE_RELEASE_LEFT position to stack" << std::endl;
      std::cout << "[IN]updateRadar(id, x, y,type, radius);." << std::endl;
      std::cout << "[IN]put radar object to opera." << std::endl;
      std::cout << "[IN]put current state to stack." << std::endl;
      std::cout << "[IN][StateRadarCentered]->[StateRadarSelected]" << std::endl;
      tools_state->push_back(this);
      tools_state->set_state(StateRadarSelected::Instance()); 
      break;
    case MOUSE_RELEASE_RIGHT :
      tools_state->set_state(StateRadarSelected::Instance()); 
      break;
    case MOUSE_MOVE :
      std::cout << "[OUT]put MOUSE_MOVE position to another stack" << std::endl;
      std::cout << "[IN]updateRadar(id, x, y, type, radius);" << std::endl;
      break;
    case BUTTON_LINE :
      tools_state->clear();
      std::cout << "[IN][StateRadarCentered]->[StateTrackLineSelected]" << std::endl;
      tools_state->set_state(StateTrackLineSelected::Instance());
      break;
    case BUTTON_CIRCLE :
      tools_state->clear();
      std::cout << "[IN][StateRadarCentered]->[StateTrackCircleSelected]" << std::endl;
      tools_state->set_state(StateTrackCircleSelected::Instance());
      break;
    case BUTTON_ECLIPSE:
      tools_state->clear();
      std::cout << "[IN][StateRadarCentered]->[StateTrackEclipseSelected]" << std::endl;
      tools_state->set_state(StateTrackEclipseSelected::Instance());
      break;
    default:
      std::cout << "[IN]No Response Event" << std::endl;
  }*/
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
  /*switch (action){
    case MOUSE_RELEASE_LEFT :
      std::cout << "[OUT]put MOUSE_RELEASE_LEFT position to stack" << std::endl;
      std::cout << "[IN]createLine(id, x, y, x1, y1);." << std::endl;
      std::cout << "[IN]put current state in stack." << std::endl;
      std::cout << "[IN][StateTrackLineSelected]->[StateTrackLineStarted]" << std::endl;
      tools_state->push_back(this);
      tools_state->set_state(StateTrackLineStarted::Instance()); 
      break;
    case BUTTON_CIRCLE :
      std::cout << "[IN][StateTrackLineSelected]->[StateTrackCircleSelected]" << std::endl;
      tools_state->set_state(StateTrackCircleSelected::Instance());
      break;
    case BUTTON_ECLIPSE:
      std::cout << "[IN][StateTrackLineSelected]->[StateTrackEclipseSelected]" << std::endl;
      tools_state->set_state(StateTrackEclipseSelected::Instance());
      break;
    default:
      std::cout << "[IN]No Response Event" << std::endl;
  }*/
}
void StateTrackLineStarted::execute(ToolsState* tools_state, Event* event){
  std::cout << "[IN]updateLine(id, x, y, x1, y1);" << std::endl;
  if(event == EventReleaseLeft::Instance()){
    DataStateLine::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    DataTrackUnitList::Instance()->push_back_line(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y());
    tools_state->set_state(StateTrackLineSelected::Instance()); 
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventMouseMove::Instance()){
    DataStateLine::Instance()->set_move(
      EventMouseMove::Instance()->x(),
      EventMouseMove::Instance()->y());
    std::cout << "[IN]updateLine(id, x, y, x1, y1);" << std::endl;
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackLineSelected::Instance());
    else
      tools_state->set_state(StateTrackLineStarted::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      tools_state->set_state(StateTrackCircleSelected::Instance());
    else
      tools_state->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    tools_state->set_state(StateTrackEclipseSelected::Instance());
  }
  /*switch (action){
    case MOUSE_RELEASE_LEFT :
      std::cout << "[OUT]put MOUSE_RELEASE_LEFT position to stack" << std::endl;
      std::cout << "[IN]updateLine(id, x, y, x1, y1);" << std::endl;
      std::cout << "[IN]put track unit line object to opera." << std::endl;
      std::cout << "[IN]put current state to stack." << std::endl;
      std::cout << "[IN][StateTrackLineStarted]->[StateTrackLineSelected]" << std::endl;
      tools_state->push_back(this);
      tools_state->set_state(StateTrackLineSelected::Instance()); 
      break;
    case MOUSE_MOVE :
      std::cout << "[OUT]put MOUSE MOVE POSITION to another stack" << std::endl;
      std::cout << "[IN]updateLine(id, x, y, x1, y1);" << std::endl;
      break;
    case BUTTON_LINE :
      if(tools_state->IsFirstTrackUnit()){
        tools_state->clear();
        std::cout << "[IN][StateTrackLineStarted]->[StateTrackLineSelected]" << std::endl;
        tools_state->set_state(StateTrackLineSelected::Instance());
      }else{
        std::cout << "[IN][StateTrackLineStarted]->[StateTrackLineStarted]" << std::endl;
        tools_state->set_state(StateTrackLineStarted::Instance());
      }
      break;
    case BUTTON_CIRCLE :
      if(tools_state->IsFirstTrackUnit()){
        tools_state->clear();
        std::cout << "[IN][StateTrackLineStarted]->[StateTrackCircleSelected]" << std::endl;
        tools_state->set_state(StateTrackCircleSelected::Instance());
      }else{
        std::cout << "[IN][StateTrackLineStarted]->[StateTrackCircleStarted]" << std::endl;
        tools_state->set_state(StateTrackCircleStarted::Instance());
      }
      break;
    case BUTTON_ECLIPSE:
      if(tools_state->IsFirstTrackUnit()){
        tools_state->clear();
        std::cout << "[StateTrackLineStarted]->[StateTrackEclipseSelected]" << std::endl;
        tools_state->set_state(StateTrackEclipseSelected::Instance());
      }else{
        std::cout << "[IN][StateTrackLineStarted]->[StateTrackEclipseStarted]" << std::endl;
        tools_state->set_state(StateTrackEclipseStarted::Instance());
      }
      break;
    default:
      std::cout << "No Response Event" << std::endl;
  }*/
}

void StateTrackCircleSelected::execute(ToolsState* tools_state, Event* event){
}
void StateTrackCircleStarted::execute(ToolsState* tools_state, Event* event){
}
void StateTrackCircleCentered::execute(ToolsState* tools_state, Event* event){

}
void StateTrackCircleSided::execute(ToolsState* tools_state, Event* event){
  
}

void StateTrackEclipseSelected::execute(ToolsState* tools_state, Event* event){

}
void StateTrackEclipseStarted::execute(ToolsState* tools_state, Event* event){
  
}
void StateTrackEclipseCentered::execute(ToolsState* tools_state, Event* event){

}
void StateTrackEclipseEnded::execute(ToolsState* tools_state, Event* event){

}
void StateTrackEclipseSided::execute(ToolsState* tools_state, Event* event){
  
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
  units_.push_back(LINE);
  units_.push_back(end_x);
  units_.push_back(end_y);
}

void DataTrackUnitList::push_back_circle(int center_x, int center_y,
    int side_x, int side_y, int angle_x, int angle_y){
  units_.push_back(CIRCLE);
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
  units_.push_back(ECLIPSE);
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
