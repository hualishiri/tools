#ifndef TOOLS_EVENT_EVENT_H_
#define TOOLS_EVENT_EVENT_H_

namespace tools {

class Event {
 public:
  virtual ~Event() {}
};

class EventMouse : public Event {
 public:
  EventMouse() : x_(0), y_(0) {}
  ~EventMouse() {}

  inline int x() const { return x_; }
  inline int y() const { return y_; }
  inline void set(int x, int y) {
    x_ = x;
    y_ = y;
  }

 private:
  int x_;
  int y_;
};

#define CONCAT(a,b) CONCAT1(a,b)
#define CONCAT1(a,b) a##b

#define EVENT(name,base)                                    \
class CONCAT(Event,name) : public EventMouse {              \
 public:                                                    \
   static CONCAT(Event,name)* Instance();                   \
                                                            \
 private:                                                   \
   CONCAT(Event,name)() {}                                  \
   ~CONCAT(Event,name)() {}                                 \
   static CONCAT(Event,name)* event_;                       \
};                                                          \
CONCAT(Event,name)* CONCAT(Event,name)::Instance() {        \
  if (!event_) event_ = new CONCAT(Event,name)();           \
  return event_;                                            \
}                                                           \
CONCAT(Event,name)* CONCAT(Event,name)::event_ = 0;         

EVENT(MousePressLeft,EventMouse)
EVENT(MousePressRight,EventMouse)
EVENT(MouseReleaseLeft,EventMouse)
EVENT(MouseReleaseRight,EventMouse)
EVENT(MouseDoubleClick,EventMouse)
EVENT(MouseMove,EventMouse)

EVENT(ButtonPointer,Event)
EVENT(ButtonLine,Event)
EVENT(ButtonCircle,Event)
EVENT(ButtonEclipse,Event)

EVENT(ButtonStart,Event)
EVENT(ButtonPause,Event)
EVENT(ButtonStep,Event)
EVENT(ButtonStop,Event)

EVENT(ButtonRadar,Event)

#undef EVENT
#undef CONCAT
#undef CONCAT1

} //namespace tools

#endif //TOOLS_EVENT_EVENT_H_
