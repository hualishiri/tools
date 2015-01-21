#include "opera_option.h"

#include <assert.h>

namespace tools {
namespace test {

class Test {
 public:
  int RunAllTest() {
    int sum = 0;
    sum += TestOperaOption();
    return sum;
  }

  int TestOperaOption() {
    for (int i = 1; i != 10; ++i) {
      OperaOption::Radar radar;
      radar.id = i;
      OperaOption::Instance()->push_back_radar(radar);
    }
    OperaOption::Instance()->pop_radar(2);
    assert(OperaOption::Instance()->size_radar() == 8);
    OperaOption::Instance()->pop_radar(15);
    assert(OperaOption::Instance()->size_radar() == 8);

    for (int i = 1; i != 10; ++i) {
      OperaOption::Object object;
      object.id = i;
      OperaOption::Instance()->push_back_object(object);
    }
    OperaOption::Instance()->pop_object(2);
    assert(OperaOption::Instance()->size_object() == 8);
    OperaOption::Instance()->pop_object(15);
    assert(OperaOption::Instance()->size_object() == 8);
    for (int i = 1; i != 10; ++i) {
      OperaOption::Track track;
      track.id = i;
      OperaOption::Instance()->push_back_track(track);
    }
    OperaOption::Instance()->pop_track(2);
    assert(OperaOption::Instance()->size_track() == 8);
    OperaOption::Instance()->pop_track(15);
    assert(OperaOption::Instance()->size_track() == 8);
    return 0;
  }
};

} //namespace test
} //namespace tools

int main(){
  return tools::test::Test().RunAllTest();
}
