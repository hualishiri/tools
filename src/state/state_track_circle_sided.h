#ifndef TOOLS_STATE_STATE_TRACK_CIRCLE_SIDED_H_
#define TOOLS_STATE_STATE_TRACK_CIRCLE_SIDED_H_

#include "state.h"

namespace tools {

class StateTrackCircleSided : public State {
public:
  static StateTrackCircleSided* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

private:
  static StateTrackCircleSided* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_TRACK_CIRCLE_SIDED_H_
