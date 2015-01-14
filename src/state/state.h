#ifndef TOOLS_STATE_H_
#define TOOLS_STATE_H_

#include <vector>

namespace tools{

class Event;
class State;
class StateRadarCentered;
class StateTrackLineSelected;
class StateTrackCircleSelected;
class StateTrackEclipseSelected;

class ToolsState{
public:
  explicit ToolsState(State* state){ state_ = state; }
  void Execute(Event* event);
  inline void set_state(State* state){ state_ = state; }
  inline State* state() const{ return state_; }
  inline void push_back( State* state ){ stack_.push_back(state); }
  inline void clear(){ stack_.clear(); }
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
  long long id_;
  double center_x_;
  double center_y_;
  double move_x_;
  double move_y_;
  inline void set_center(double x, double y){
    center_x_ = x;
    center_y_ = y;
  }
  inline void set_move(double x, double y){
    move_x_ = x;
    move_y_ = y;
  }
  inline void set_id(long long id){ id_ = id; }
  inline long long id() const { return id_; }
  inline double center_x() const { return center_x_; }
  inline double center_y() const { return center_y_; }
  inline double move_x() const { return move_x_; }
  inline double move_y() const { return move_y_; }

  static DataStateRadar* data_;
  static DataStateRadar* Instance();
};

class DataRadarList{
public:
  inline void clear(){ radars_.clear(); }
  inline void push_back_radar(double center_x, double center_y,
      double radius_x, double radius_y){ 
    radars_.push_back(center_x);
    radars_.push_back(center_y);
    radars_.push_back(radius_x);
    radars_.push_back(radius_y);
  }
  inline void pop_back_radar(){ 
    if(radars_.size() > 4){
      radars_.pop_back(); 
      radars_.pop_back(); 
      radars_.pop_back(); 
      radars_.pop_back(); 
    }
  }
  inline std::size_t size() const { return radars_.size(); }
  inline std::vector<double> radars() const { return radars_; }
  
  static DataRadarList* Instance();
private:
  std::vector<double> radars_;
  static DataRadarList* radar_list_;
};

class DataStateLine{
public:
  friend class StateTrackLineSelected;
  friend class StateTrackLineStarted;

  static DataStateLine* Instance();
private:
  double start_x_;
  double start_y_;
  double move_x_;
  double move_y_;
  inline double start_x() const { return start_x_; }
  inline double start_y() const { return start_y_; }
  inline double move_x() const { return move_x_; }
  inline double move_y() const { return move_y_; }
  inline void set_start(double x, double y){
    start_x_ = x;
    start_y_ = y;
  }
  inline void set_move(double x, double y){
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
    double start_x;
    double start_y;
    double center_x;
    double center_y;
    double side_x;
    double side_y;
    double angle_x;
    double angle_y;
  };
  struct Move{
    double x;
    double y;
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


class DataTrackUnitList{
public:
  static DataTrackUnitList* Instance();
  enum TrackUnitType{ LINE, CIRCLE, ECLIPSE };
  inline void set_start(double x, double y){
    start_x_ = x;
    start_y_ = y;
  }
  inline void push_back_line(double end_x, double end_y);
  inline void push_back_circle(
      double center_x, double center_y,
      double side_x, double size_y,
      double angle_x, double angle_y
      );
  void push_back_eclipse(
      double center_x, double center_y,
      double end_x, double end_y,
      double side_x, double side_y,
      double angle_x, double angle_y
      );
  inline std::size_t size() const { return units_.size(); }
  inline void clear(){ units_.clear(); }
  inline bool empty() const { return units_.empty(); }
  inline std::vector<double> track_units() const { return units_; }
private:
  std::vector<int> units_flag_;
  std::vector<double> units_;
  double start_x_;
  double start_y_;
  
  static DataTrackUnitList* data_;
};

} //namespace tools

#endif //TOOLS_STATE_H_ 
