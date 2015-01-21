#include "state_internal_handle.h"

#include "event/event.h"
#include "webkit/webkit.h"
#include "state/data_state_line.h"
#include "state/data_state_circle.h"
#include "state/data_state_eclipse.h"
#include "state/data_track_unit_list.h"
#include "state/opera_context.h"
#include "state/opera_option.h"
#include "state/state_track_line_selected.h"
#include "state/state_track_line_started.h"
#include "state/state_track_circle_selected.h"
#include "state/state_track_circle_started.h"
//#include "state/state_track_eclipse_selected.h"
//#include "state/state_track_eclipse_started.h"

namespace tools {

bool IsEventInEditing(Event* event) {
  if (event == EventReleaseLeft::Instance() ||
      event == EventReleaseRight::Instance() ||
      event == EventPressLeft::Instance() ||
      event == EventPressRight::Instance() ||
      event == EventMouseDoubleClick::Instance() ||
      event == EventMouseMove::Instance() ||
      event == EventWheel::Instance() ||
      event == EventButtonLine::Instance() ||
      event == EventButtonCircle::Instance() ||
      event == EventButtonEclipse::Instance())
    return true;
  return false;
}

bool IsEventInButtonLineCircleEclipse(Event* event) {
  if (event == EventButtonLine::Instance() ||
      event == EventButtonCircle::Instance() ||
      event == EventButtonEclipse::Instance())
    return true;
  return false;
}

void StateSelectedEventHandle(OperaContext* opera_context, Event* event) {
  if (event == EventButtonLine::Instance())
    opera_context->set_state(StateTrackLineSelected::Instance());
  else if (event == EventButtonCircle::Instance())
    opera_context->set_state(StateTrackCircleSelected::Instance());
  else if (event == EventButtonEclipse::Instance())
    opera_context->set_state(0/*StateTrackEclipseSelected::Instance()*/);
  //TODO: something
}

void StateAfterSelectedEventHandle(OperaContext* opera_context, Event* event) {
  if (DataTrackUnitList::Instance()->empty()){
    if (event == EventButtonLine::Instance())
      opera_context->set_state(StateTrackLineSelected::Instance());   
    else if (event == EventButtonCircle::Instance())
      opera_context->set_state(StateTrackCircleSelected::Instance());
    else if (event == EventButtonEclipse::Instance())
      opera_context->set_state(0/*StateTrackEclipseSeleted::Instance()*/);
      //TODO: something
  } else {
    if (event == EventButtonLine::Instance())
      opera_context->set_state(StateTrackLineStarted::Instance());
    else if (event == EventButtonCircle::Instance())
      opera_context->set_state(0/*StateTrackCircleStarted::Instance()*/);
    //TODO: something
    else if (event == EventButtonEclipse::Instance())
      opera_context->set_state(0/*StateTrackEclipseStarted::Instance()*/);
    //TODO: something
  }
}

void StateCircleEventReleaseRightHandle(long long id,
                                        OperaContext* opera_context) {
  JSDeleteCircle js_delete_circle(id);
  Webkit::Instance()->execute(js_delete_circle);
  if (!DataTrackUnitList::Instance()->empty()) {
    OperaOption::Instance()->push_back_track(
        DataTrackUnitList::Instance()->track());
    DataTrackUnitList::Instance()->clear();
  }
  opera_context->set_state(StateTrackCircleSelected::Instance()); 
}

void SetDataLineCircleEclipse(long long id, double start_x, double start_y) {
  DataStateLine::Instance()->set_id(id);
  DataStateLine::Instance()->set_start(start_x, start_y);
  DataStateCircle::Instance()->circle_.id = id;
  DataStateCircle::Instance()->circle_.start_x = start_x;
  DataStateCircle::Instance()->circle_.start_y = start_y;
  //DataStateEclipse::Instance()->eclipse_.id = id;
  //TODO: something
}

} //namespace tools
