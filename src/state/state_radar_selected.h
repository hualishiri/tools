#ifndef TOOLS_STATE_STATE_RADAR_SELECTED_H_
#define TOOLS_STATE_STATE_RADAR_SELECTED_H_

#include "state/state.h"

namespace tools {
  
class Event;
class OperaContext;

class StateRadarSelected : public State {
 public:
  static StateRadarSelected* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

 private:
  StateRadarSelected() {}
  StateRadarSelected(const StateRadarSelected&);
  StateRadarSelected& operator=(const StateRadarSelected&);

  void EventReleaseHandle();
  void EventWheelHandle();

  static StateRadarSelected* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_RADAR_SELECTED_H_
