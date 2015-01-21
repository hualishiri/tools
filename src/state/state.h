#ifndef TOOLS_STATE_H_
#define TOOLS_STATE_H_

#include <vector>

namespace tools{

class Event;
class OperaContext;

class State{
 public:
  virtual void execute(OperaContext* opera_context, Event* event) = 0;
  virtual ~State() = 0;
};

/*




class StateTrackEclipseSelected : public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateTrackEclipseSelected* Instance();
private:
  static StateTrackEclipseSelected* state_;
};

class StateTrackEclipseStarted: public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateTrackEclipseStarted* Instance();
private:
  static StateTrackEclipseStarted* state_;
};

class StateTrackEclipseCentered : public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateTrackEclipseCentered* Instance();
private:
  static StateTrackEclipseCentered* state_;
};

class StateTrackEclipseEnded : public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateTrackEclipseEnded* Instance();
private:
  static StateTrackEclipseEnded* state_;
};

class StateTrackEclipseSided: public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateTrackEclipseSided* Instance();
private:
  static StateTrackEclipseSided* state_;
};

class StateContralStarted : public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateContralStarted* Instance();
private:
  static StateContralStarted* state_;
};

class StateContralSteped: public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateContralSteped* Instance();
private:
  static StateContralSteped* state_;
};

class StateContralPaused : public State{
public:
  virtual void execute(OperaContext* opera_context, Event* event);
  static StateContralPaused* Instance();
private:
  static StateContralPaused* state_;
};


class DataStateEclipse{
public:
  friend class StateTrackEclipseSelected;
  friend class StateTrackEclipseStarted;
  friend class StateTrackEclipseCentered;
  friend class StateTrackEclipseEnded;
  friend class StateTrackEclipseSided;
  static DataStateEclipse* Instance();
private:
  struct Eclipse{
    double start_x;
    double start_y;
    double center_x;
    double center_y;
    double end_x;
    double end_y;
    double side_x;
    double side_y;
    double angle_x;
    double angle_y;
  };
  struct Move{
    double x;
    double y;
  };
  Eclipse eclipse_;
  Move move_;
  static DataStateEclipse* data_;
};
*/

} //namespace tools

#endif //TOOLS_STATE_H_ 
