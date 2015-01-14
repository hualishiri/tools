#include "opera_option.h"

namespace tools{

OperaOption* OperaOption::option_ = 0;

void OperaOption::pop_radar(long long id){
  std::vector<Radar>::iterator iter = radars_.begin();
  for(iter; iter != radars_.end(); ++iter){
    if(iter->id == id){
      radars_.erase(iter);
      return;
    }
  }
}

void OperaOption::pop_object(long long id){
  std::vector<Object>::iterator iter = objects_.begin();
  for(iter; iter != objects_.end(); ++iter){
    if(iter->id == id){
      objects_.erase(iter);
      return;
    }
  }
}

void OperaOption::pop_track(long long id){
  std::vector<Track>::iterator iter = tracks_.begin();
  for(iter; iter != tracks_.end(); ++iter){
    if(iter->id == id){
      tracks_.erase(iter);
      return;
    }
  }
}

OperaOption* OperaOption::Instance(){
  if(!option_) option_ = new OperaOption;
  return option_;
}

} //namespace tools
