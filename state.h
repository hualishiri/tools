#ifndef TOOLS_STATE_H_
#define TOOLS_STATE_H_

#include <vector>

#include "event.h"

namespace tools{

class State;
class StateRadarCentered;
class StateTrackLineSelected;
class StateTrackCircleSelected;
class StateTrackEclipseSelected;

class ToolsState{
public:
  ToolsState(State* state){
    state_ = state;
  }
  void Execute(Event* event);
  void set_state(State* state){ state_ = state; }
  State* state() const{ return state_; }
  void push_back(State* state){stack_.push_back(state);}
  void clear(){stack_.clear();}
  bool IsFirstTrackUnit() const;
  void pop(int n){ 
    for(int i=0; i!=n; ++i)
      stack_.pop_back();
  }
  
private:
  State* state_;
  std::vector<State*> stack_;
};

class State{
public:
  virtual void execute(ToolsState* tools_state, Event* event) = 0;
  virtual ~State() = 0;
};


class StateRadarSelected : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateRadarSelected* Instance();
private:
  static StateRadarSelected* state_;
  StateRadarSelected(){}
};


class StateRadarCentered : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateRadarCentered* Instance();
private:
  static StateRadarCentered* state_;
  StateRadarCentered(){}
};

class StateTrackLineSelected: public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackLineSelected* Instance();
private:
  static StateTrackLineSelected* state_;
};

class StateTrackLineStarted : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackLineStarted* Instance();
private:
  static StateTrackLineStarted* state_;
};

class StateTrackCircleSelected: public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackCircleSelected* Instance();
private:
  static StateTrackCircleSelected* state_;
};

class StateTrackCircleStarted: public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackCircleStarted* Instance();
private:
  static StateTrackCircleStarted* state_;
};

class StateTrackCircleCentered : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackCircleCentered* Instance();
private:
  static StateTrackCircleCentered* state_;
};

class StateTrackCircleSided : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackCircleSided* Instance();
private:
  static StateTrackCircleSided* state_;
};

class StateTrackEclipseSelected : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackEclipseSelected* Instance();
private:
  static StateTrackEclipseSelected* state_;
};

class StateTrackEclipseStarted: public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackEclipseStarted* Instance();
private:
  static StateTrackEclipseStarted* state_;
};

class StateTrackEclipseCentered : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackEclipseCentered* Instance();
private:
  static StateTrackEclipseCentered* state_;
};

class StateTrackEclipseEnded : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackEclipseEnded* Instance();
private:
  static StateTrackEclipseEnded* state_;
};

class StateTrackEclipseSided: public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateTrackEclipseSided* Instance();
private:
  static StateTrackEclipseSided* state_;
};

class StateContralStarted : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateContralStarted* Instance();
private:
  static StateContralStarted* state_;
};

class StateContralSteped: public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateContralSteped* Instance();
private:
  static StateContralSteped* state_;
};

class StateContralPaused : public State{
public:
  virtual void execute(ToolsState* tools_state, Event* event);
  static StateContralPaused* Instance();
private:
  static StateContralPaused* state_;
};

class DataStateRadar{
  friend class StateRadarSelected;
  friend class StateRadarCentered;
private:
  DataStateRadar():center_x_(0), center_y_(0),
    move_x_(0), move_y_(0){}
  int center_x_;
  int center_y_;
  int move_x_;
  int move_y_;
  void set_center(int x, int y){
    center_x_ = x;
    center_y_ = y;
  }
  void set_move(int x, int y){
    move_x_ = x;
    move_y_ = y;
  }
  int center_x() const { return center_x_; }
  int center_y() const { return center_y_; }
  int move_x() const { return move_x_; }
  int move_y() const { return move_y_; }

  static DataStateRadar* data_;
  static DataStateRadar* Instance();
};

class DataRadarList{
public:
  void clear(){ radars_.clear(); }
  void push_back_radar(int center_x, int center_y,
      int radius_x, int radius_y){ 
    radars_.push_back(center_x);
    radars_.push_back(center_y);
    radars_.push_back(radius_x);
    radars_.push_back(radius_y);
  }
  void pop_back_radar(){ 
    if(radars_.size() > 4){
      radars_.pop_back(); 
      radars_.pop_back(); 
      radars_.pop_back(); 
      radars_.pop_back(); 
    }
  }
  std::size_t size() const { return radars_.size(); }
  std::vector<int> radars() const { return radars_; }
  
  static DataRadarList* Instance();
private:
  std::vector<int> radars_;
  static DataRadarList* radar_list_;
};

class DataStateLine{
public:
  friend class StateTrackLineSelected;
  friend class StateTrackLineStarted;

  static DataStateLine* Instance();
private:
  int start_x_;
  int start_y_;
  int move_x_;
  int move_y_;
  int start_x() const { return start_x_; }
  int start_y() const { return start_y_; }
  int move_x() const { return move_x_; }
  int move_y() const { return move_y_; }
  void set_start(int x, int y){
    start_x_ = x;
    start_y_ = y;
  }
  void set_move(int x, int y){
    move_x_ = x;
    move_y_ = y;
  }
  DataStateLine(){}
  static DataStateLine* data_;
};


class DataStateCircle{
public:
  friend class StateTrackCircleStarted;
  friend class StateTrackCircleSelected;
  friend class StateTrackCircleCentered;
  friend class StateTrackCircleSided;
  static DataStateCircle* Instance();
private:
  struct Circle{
    int start_x;
    int start_y;
    int center_x;
    int center_y;
    int side_x;
    int side_y;
    int angle_x;
    int angle_y;
  };
  struct Move{
    int x;
    int y;
  };
  Circle circle_;
  Move move_;
  static DataStateCircle* data_;
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
    int start_x;
    int start_y;
    int center_x;
    int center_y;
    int end_x;
    int end_y;
    int side_x;
    int side_y;
    int angle_x;
    int angle_y;
  };
  struct Move{
    int x;
    int y;
  };
  Eclipse eclipse_;
  Move move_;
  static DataStateEclipse* data_;
};


class DataTrackUnitList{
public:
  static DataTrackUnitList* Instance();
  enum TrackUnitType{
    LINE,
    CIRCLE,
    ECLIPSE
  };
  void set_start(int x, int y){
    start_x_ = x;
    start_y_ = y;
  }
  void push_back_line(int end_x, int end_y);
  void push_back_circle(
      int center_x, int center_y,
      int side_x, int size_y,
      int angle_x, int angle_y
      );
  void push_back_eclipse(
      int center_x, int center_y,
      int end_x, int end_y,
      int side_x, int side_y,
      int angle_x, int angle_y
      );
  std::size_t size() const { return units_.size(); }
  void clear(){ units_.clear(); }
  bool empty() const { return units_.empty(); }
  std::vector<int> track_units() const { return units_; }
private:
  std::vector<int> units_;
  int start_x_;
  int start_y_;
  
  static DataTrackUnitList* data_;
};

} //namespace tools

#endif //TOOLS_STATE_H_ 
