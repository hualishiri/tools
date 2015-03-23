#include "opera/opera_option.h"

namespace tools {

OperaOption* OperaOption::opera_option_ = 0;

OperaOption* OperaOption::Instance() {
  if (opera_option_ == 0)
    opera_option_ = new OperaOption();
  return opera_option_;
}

void OperaOption::pop_radar(long long id) {
  std::vector<Radar>::iterator iter = radars_.begin();
  for (; iter != radars_.end(); ++iter) {
    if (iter->id == id) {
      radars_.erase(iter);
      return;
    }
  }
}

void OperaOption::pop_object(long long id) {
  std::vector<Object>::iterator iter = objects_.begin();
  for (; iter != objects_.end(); ++iter) {
    if (iter->id == id) {
      objects_.erase(iter);
      return;
    }
  }
}

void OperaOption::pop_track(long long id) {
  std::vector<Track>::iterator iter = tracks_.begin();
  for (; iter != tracks_.end(); ++iter) {
    if (iter->id == id) {
      tracks_.erase(iter);
      return;
    }
  }
}

} //namespace tools
