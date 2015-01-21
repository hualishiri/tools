#ifndef TOOLS_STATE_STATE_INTERNAL_HANDLE_H_
#define TOOLS_STATE_STATE_INTERNAL_HANDLE_H_

namespace tools {

class Event;
class OperaContext;
class State;
  
bool IsEventInEditing(Event* event);
bool IsEventInButtonLineCircleEclipse(Event* event);
void StateSelectedEventHandle(OperaContext* opera_context, Event* event);
void StateAfterSelectedEventHandle(OperaContext* opera_context, Event* event);
void StateCircleEventReleaseRightHandle(long long id,
                                        OperaContext* opera_context);
void SetDataLineCircleEclipse(long long id, double start_x, double start_y);

} //namespace tools

#endif //TOOLS_STATE_STATE_INTERNAL_HANDLE_H_
