#ifndef TOOLS_STATE_STATE_TRACK_CIRCLE_CENTERED_H_
#define TOOLS_STATE_STATE_TRACK_CIRCLE_CENTERED_H_

#include "state.h"

namespace tools {

class Event;
class OperaContext;

class StateTrackCircleCentered : public State{
 public:
  static StateTrackCircleCentered* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

 private:
  static StateTrackCircleCentered* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_TRACK_CIRCLE_CENTERED_H_
