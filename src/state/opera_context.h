#ifndef TOOLS_STATE_OPERA_CONTENT_H_
#define TOOLS_STATE_OPERA_CONTENT_H_


namespace tools {

class State;
class Event;

class OperaContext {
 public:
  explicit OperaContext(State* state) { state_ = state; }

  void Execute(Event* event);
  inline void set_state(State* state) { state_ = state; }
  inline State* state() const { return state_; }
  
 private:
  State* state_;
};

} //namespace tools

#endif //TOOLS_STATE_OPERA_CONTENT_H_
