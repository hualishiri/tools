#include "state.h"

namespace tools{

State::~State() {}

/*
StateTrackEclipseSelected* StateTrackEclipseSelected::state_ = 0;
StateTrackEclipseStarted* StateTrackEclipseStarted::state_ = 0;
StateTrackEclipseCentered* StateTrackEclipseCentered::state_ = 0;
StateTrackEclipseEnded* StateTrackEclipseEnded::state_ = 0;
StateTrackEclipseSided* StateTrackEclipseSided::state_ = 0;
StateContralStarted* StateContralStarted::state_ = 0;
StateContralSteped* StateContralSteped::state_ = 0;
StateContralPaused* StateContralPaused::state_ = 0;

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
*/


/*

void StateTrackCircleCentered::execute(OperaContext* opera_context, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateCircle::Instance()->circle_.side_x = EventReleaseLeft::Instance()->x();
    DataStateCircle::Instance()->circle_.side_y = EventReleaseLeft::Instance()->y();
    std::cout << "upDateCircle();" << std::endl;
    opera_context->set_state(StateTrackCircleSided::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackLineSelected::Instance());
    else
      opera_context->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackCircleSided::execute(OperaContext* opera_context, Event* event){
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
    opera_context->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackLineSelected::Instance());
    else
      opera_context->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}

void StateTrackEclipseSelected::execute(OperaContext* opera_context, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.start_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.start_y = EventReleaseLeft::Instance()->y();
    DataTrackUnitList::Instance()->set_start(
      EventReleaseLeft::Instance()->x(),
      EventReleaseLeft::Instance()->y()
    );
    opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    opera_context->set_state(StateTrackLineSelected::Instance());
  }
  if(event == EventButtonCircle::Instance()){
    opera_context->set_state(StateTrackCircleSelected::Instance());
  }
  if(event == EventButtonEclipse::Instance()){
    opera_context->set_state(StateTrackEclipseSelected::Instance());
  }
}

void StateTrackEclipseStarted::execute(OperaContext* opera_context, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.center_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.center_y = EventReleaseLeft::Instance()->y();
    opera_context->set_state(StateTrackEclipseCentered::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackLineSelected::Instance());
    else
      opera_context->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackEclipseCentered::execute(OperaContext* opera_context, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.end_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.end_y = EventReleaseLeft::Instance()->y();
    opera_context->set_state(StateTrackEclipseEnded::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackLineSelected::Instance());
    else
      opera_context->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackEclipseEnded::execute(OperaContext* opera_context, Event* event){
  if(event == EventReleaseLeft::Instance()){
    DataStateEclipse::Instance()->eclipse_.side_x = EventReleaseLeft::Instance()->x();
    DataStateEclipse::Instance()->eclipse_.side_y = EventReleaseLeft::Instance()->y();
    opera_context->set_state(StateTrackEclipseSided::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackLineSelected::Instance());
    else
      opera_context->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
}
void StateTrackEclipseSided::execute(OperaContext* opera_context, Event* event){
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
    opera_context->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventReleaseRight::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
  }
  if(event == EventWheel::Instance()){
    //TODO: something
  }
  if(event == EventButtonLine::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackLineSelected::Instance());
    else
      opera_context->set_state(StateTrackLineStarted::Instance());
    return;
  }
  if(event == EventButtonCircle::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else
      opera_context->set_state(StateTrackCircleStarted::Instance());
    return;
  }
  if(event == EventButtonEclipse::Instance()){
    if(DataTrackUnitList::Instance()->empty())
      opera_context->set_state(StateTrackEclipseSelected::Instance());
    else
      opera_context->set_state(StateTrackEclipseStarted::Instance());
    return;
  }
  
}

void StateContralStarted::execute(OperaContext* opera_context, Event* event){

}
void StateContralSteped::execute(OperaContext* opera_context, Event* event){
  
}
void StateContralPaused::execute(OperaContext* opera_context, Event* event){

}*/
/*
DataStateEclipse* DataStateEclipse::data_ = 0;


DataStateEclipse* DataStateEclipse::Instance(){
  if(!data_) data_ = new DataStateEclipse();
  return data_;
}
*/

} //namespace tools
