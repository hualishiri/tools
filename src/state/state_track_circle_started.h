#ifndef TOOLS_STATE_STATE_TRACK_CIRCLE_STARTED_H_
#define TOOLS_STATE_STATE_TRACK_CIRCLE_STARTED_H_

#include "state.h"

namespace tools {

class Event;
class OperaContext;

class StateTrackCircleStarted : public State {
 public:
  static StateTrackCircleStarted* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

private:
  static StateTrackCircleStarted* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_TRACK_CIRCLE_STARTED_H_
