#ifndef TOOLS_STATE_STATE_RADAR_CENTERED_H_
#define TOOLS_STATE_STATE_RADAR_CENTERED_H_

#include "state/state.h"

namespace tools {

class OperaOption;

class StateRadarCentered : public State {
 public:
  static StateRadarCentered* Instance();
  virtual void execute(OperaContext* opera_context, Event* event);

 private:
  StateRadarCentered() {}
  StateRadarCentered(const StateRadarCentered&);
  StateRadarCentered& operator=(const StateRadarCentered&);

  static StateRadarCentered* state_;
};

} //namespace tools

#endif //TOOLS_STATE_STATE_RADAR_CENTERED_H_
