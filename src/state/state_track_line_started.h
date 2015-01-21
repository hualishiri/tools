#ifndef TOOLS_STATE_STATE_TRACK_LINE_STARTED_H_
#define TOOLS_STATE_STATE_TRACK_LINE_STARTED_H_

#include "state.h"

namespace tools {

class Event;
class OperaContext;

class StateTrackLineStarted : public State {
 public:
  static StateTrackLineStarted* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

 private:
  void EventReleaseLeftHandle();
  void EventReleaseRightHandle();
  void EventMouseMoveHandle();
  void EventOtherHandle();

  static StateTrackLineStarted* state_;

  OperaContext* opera_context_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_TRACK_LINE_STARTED_H_
