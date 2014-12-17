#include "opera.h"

#include <cassert>

namespace tools{

void OperaWar::Initialize(OperaOption* option){
  assert(option->tracks->size() == option->targets->size());

  option_ = option;
  time_current_ = 0;
  time_sum_ = GetSumTime();
}
bool OperaWar::Valid(){
  return time_current_ <= time_sum_;
}
void OperaWar::Next(){
  time_current_ += option_->kInternal;

}
void OperaWar::GetState(OperaState* state){
  const unsigned int batchs = option_->targets->size();

  /*for (auto iter = option_->targets->begin();
    iter != option_->targets->end(); ++iter, ++iter_option){
    if ((*iter)->Valid()){
      (*iter)->GetState(*iter_option);
      (*iter)->Next();
    }
  }*/

  //TODO: something

  state->target_states = option_->target_init_states;
  state->sensor_states = option_->sensor_states;
}
void OperaWar::Finalize(){
  //TODO: Something
}

unsigned long OperaWar::GetSumTime() const{
  //TODO: Something
  return 1000;
}

} //namespace tools
