#include "state.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "event/event.h"
#include "map/map.h"
#include "webkit/webkit.h"

namespace tools{

void WebView(const char* str){
  std::cout << str << std::endl;
}

namespace test{

class Test{
 public:
  void RunAllTest() {
    //TestRadarFunction();
    TestRadar();
  }
  void TestRadarFunction() {
    std::vector<State*> states;
    std::vector<State*> states_init;
    std::vector<Event*> events;

    Map::Instance()->set_zoom(14);
    Map::Instance()->set_origin_x(1075954).set_origin_y(1559345);
    Map::Instance()->set_width(200).set_height(200);
    EventReleaseLeft::Instance()->set(0, 0);
    EventWheel::Instance()->set_angle(120);

    states_init.push_back(StateRadarSelected::Instance());
    states_init.push_back(StateRadarCentered::Instance());
    states_init.push_back(StateTrackLineSelected::Instance());
    states_init.push_back(StateTrackLineStarted::Instance());
    states_init.push_back(StateTrackCircleSelected::Instance());
    states_init.push_back(StateTrackCircleStarted::Instance());
    states_init.push_back(StateTrackCircleCentered::Instance());
    states_init.push_back(StateTrackCircleSided::Instance());
    states_init.push_back(StateTrackEclipseSelected::Instance());
    states_init.push_back(StateTrackEclipseStarted::Instance());
    states_init.push_back(StateTrackEclipseCentered::Instance());
    states_init.push_back(StateTrackEclipseEnded::Instance());
    states_init.push_back(StateTrackEclipseSided::Instance());
    states_init.push_back(StateContralStarted::Instance());
    states_init.push_back(StateContralSteped::Instance());
    states_init.push_back(StateContralPaused::Instance());

    //states_init.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    /*
    //states_init.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarSelected::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    states.push_back(StateRadarCentered::Instance());
    
    //states_init.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    
    
    //states_init.push_back(Statetracklinestarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    states.push_back(StateTrackLineStarted::Instance());
    

    //states_init.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());

    
    //states_init.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleStarted::Instance());

    //states_init.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());
    states.push_back(StateTrackCircleCentered::Instance());

    //states_init.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleStarted::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());
    states.push_back(StateTrackCircleSided::Instance());

    //states_init.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());

    
    //states_init.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());

    //states_init.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());
    states.push_back(StateTrackEclipseCentered::Instance());

    //states_init.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());
    states.push_back(StateTrackEclipseEnded::Instance());

    
    //states_init.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseStarted::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackLineSelected::Instance());
    states.push_back(StateTrackCircleSelected::Instance());
    states.push_back(StateTrackEclipseSelected::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    states.push_back(StateTrackEclipseSided::Instance());
    */
    /////////////////////////////////////////////////////
    events.push_back(EventPressLeft::Instance());
    events.push_back(EventPressRight::Instance());
    events.push_back(EventReleaseLeft::Instance());
    events.push_back(EventReleaseRight::Instance());
    
    events.push_back(EventMouseDoubleClick::Instance());
    events.push_back(EventMouseMove::Instance());

    events.push_back(EventButtonLine::Instance());
    events.push_back(EventButtonCircle::Instance());
    events.push_back(EventButtonEclipse::Instance());

    events.push_back(EventWheel::Instance());

    events.push_back(EventButtonStart::Instance());
    events.push_back(EventButtonStep::Instance());
    events.push_back(EventButtonPause::Instance());
    events.push_back(EventButtonStop::Instance());
    events.push_back(EventButtonAnalysis::Instance());
    
    int count = events.size();
    for(int i=0; i!=count; ++i){
    events.push_back(EventPressLeft::Instance());
    events.push_back(EventPressRight::Instance());
    events.push_back(EventReleaseLeft::Instance());
    events.push_back(EventReleaseRight::Instance());

    events.push_back(EventMouseDoubleClick::Instance());
    events.push_back(EventMouseMove::Instance());
    
    events.push_back(EventButtonLine::Instance());
    events.push_back(EventButtonCircle::Instance());
    events.push_back(EventButtonEclipse::Instance());
  
    events.push_back(EventWheel::Instance());

    events.push_back(EventButtonStart::Instance());
    events.push_back(EventButtonStep::Instance());
    events.push_back(EventButtonPause::Instance());
    events.push_back(EventButtonStop::Instance());

    events.push_back(EventButtonAnalysis::Instance());
    }
    
    Internal(&states_init,
        &events, &states, count);
  }
  void TestRadar(){
    Map::Instance()->zoom(10);
    Map::Instance()->set_origin_x(67247);
    Map::Instance()->set_origin_y(97459);
    Map::Instance()->set_width(200);
    Map::Instance()->set_height(200);
    Webkit::Instance()->set_page(WebView);

    State* init_state = StateRadarSelected::Instance();
    ToolsState tools_state(init_state);


    EventReleaseLeft::Instance()->set(0, 0);
    tools_state.Execute(EventReleaseLeft::Instance());
    
    EventReleaseLeft::Instance()->set(100, 100);
    tools_state.Execute(EventReleaseLeft::Instance());

    EventReleaseLeft::Instance()->set(20, 20);
    tools_state.Execute(EventReleaseLeft::Instance());
    
    EventReleaseLeft::Instance()->set(150, 150);
    tools_state.Execute(EventReleaseLeft::Instance());

    EventWheel::Instance()->set_angle(120);
    EventWheel::Instance()->set_x(10);
    EventWheel::Instance()->set_y(10);
    tools_state.Execute(EventWheel::Instance());


    /*
    typedef Event* EVENT;
    typedef State* STATE;
    EVENT events[] = {
      EventReleaseLeft::Instance(),
      EventReleaseLeft::Instance(),
      EventReleaseLeft::Instance(),
      EventReleaseLeft::Instance(),
      EventReleaseLeft::Instance(),
    };
    STATE states[] = {
      StateRadarCentered::Instance(),
      StateRadarSelected::Instance(),
      StateRadarCentered::Instance(),
      StateRadarSelected::Instance(),
      StateRadarCentered::Instance(),
    };
    ToolsState tools_state(init_state);
    int length_events = sizeof(events)/sizeof(EVENT);
    int length_states = sizeof(states)/sizeof(STATE);
    for(int i=0; i!=length_events; ++i){
      tools_state.Execute(events[i]);
      assert(tools_state.state() == states[i]);
    }*/
  }

  void Internal(std::vector<State*> *state_init, 
      std::vector<Event*>* events,
      std::vector<State*> *states,
      int count){
      ToolsState tools(0);
      for(int i=0; i!=states->size(); ++i){
        DataTrackUnitList::Instance()->clear();
        tools.set_state((*state_init)[i/count]);
        tools.Execute((*events)[i]);
        assert(tools.state() == (*states)[i]);
      }
  }
};

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
  return 0;
}
