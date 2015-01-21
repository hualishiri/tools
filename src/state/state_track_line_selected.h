#ifndef TOOLS_STATE_STATE_TRACK_LINE_SELECTED_H_
#define TOOLS_STATE_STATE_TRACK_LINE_SELECTED_H_

#include "state.h"

namespace tools {

class Event;
class OperaContext;

class StateTrackLineSelected : public State {
 public:
  static StateTrackLineSelected* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

 private:
  StateTrackLineSelected() {}
  StateTrackLineSelected(const StateTrackLineSelected&);
  StateTrackLineSelected& operator=(const StateTrackLineSelected&);

  static StateTrackLineSelected* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_TRACK_LINE_SELECTED_H_
