#ifndef TOOLS_STATE_STATE_TRACK_CIRCLE_SELECTED_H_
#define TOOLS_STATE_STATE_TRACK_CIRCLE_SELECTED_H_

#include "state.h"

namespace tools {

class Event;
class OperaContext;

class StateTrackCircleSelected : public State {
 public:
  static StateTrackCircleSelected* Instance();

  virtual void execute(OperaContext* opera_context, Event* event);

 private:
  static StateTrackCircleSelected* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_TRACK_CIRCLE_SELECTED_H_
