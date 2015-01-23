#ifndef TOOLS_EVENT_H_
#define TOOLS_EVENT_H_

namespace tools {

class Event {
 public:
  virtual ~Event() = 0;
};

class EventMouse : public Event {
 public:
  virtual  ~EventMouse() = 0;
  EventMouse() : x_(0), y_(0){}
  inline int x() const { return x_; }
  inline int y() const { return y_; }
  inline int set(int x, int y){
    x_ = x;
    y_ = y;
  }
private:
  int x_;
  int y_;
};

class EventPressLeft : public EventMouse{
public:
  static EventPressLeft* Instance();
private:
  EventPressLeft(){}
  static EventPressLeft* event_;
};

class EventPressRight : public EventMouse{
public:
  static EventPressRight* Instance();
private:
  EventPressRight(){}
  static EventPressRight* event_;
};

class EventReleaseLeft : public EventMouse{
public:
  static EventReleaseLeft* Instance();
private:
  EventReleaseLeft(){}
  static EventReleaseLeft* event_;
};

class EventReleaseRight : public EventMouse{
public:
  static EventReleaseRight* Instance();
private:
  EventReleaseRight(){}
  static EventReleaseRight* event_;
};

class EventMouseDoubleClick: public EventMouse{
public:
  static EventMouseDoubleClick* Instance();
private:
  EventMouseDoubleClick(){}
  static EventMouseDoubleClick* event_;
};

class EventMouseMove : public EventMouse{
public:
  static EventMouseMove* Instance();
private:
  EventMouseMove(){}
  static EventMouseMove* event_;
};

class EventWheel : public Event{
public:
  static EventWheel* Instance();
  inline int angle() const{ return angle_; }
  inline void set_angle(int angle){ angle_ = angle; }
  inline int x() const { return x_; }
  inline int y() const { return y_; }
  inline int set_x(int x) { x_ = x; }
  inline int set_y(int y) { y_ = y; }
private:
  EventWheel(){}
  int angle_;
  int x_;
  int y_;
  static EventWheel* event_;
};

class EventButtonLine : public Event{
public:
  static EventButtonLine* Instance();
private:
  static EventButtonLine* event_;
};

class EventButtonCircle : public Event{
public:
  static EventButtonCircle* Instance();
private:
  static EventButtonCircle* event_;
};

class EventButtonEclipse : public Event{
public:
  static EventButtonEclipse* Instance();
private:
  static EventButtonEclipse* event_;
};

class EventButtonStart: public Event{
public:
  static EventButtonStart* Instance();
private:
  static EventButtonStart* event_;
};

class EventButtonStep: public Event{
public:
  static EventButtonStep* Instance();
private:
  static EventButtonStep* event_;
};

class EventButtonPause: public Event{
public:
  static EventButtonPause* Instance();
private:
  static EventButtonPause* event_;
};

class EventButtonStop: public Event{
public:
  static EventButtonStop* Instance();
private:
  static EventButtonStop* event_;
};

class EventButtonAnalysis: public Event{
public:
  static EventButtonAnalysis* Instance();
private:
  static EventButtonAnalysis* event_;
};

class EventButtonRadar : public Event{
public:
  static EventButtonRadar* Instance();

private:
  static EventButtonRadar* event_;
};

} //namespace tools

#endif 
