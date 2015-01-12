#include "event.h"

#include <cassert>

namespace tools{
namespace test{

class Test{
public:
  void RunAllTest(){
    TestFunction();
  }

  void TestFunction(){
    EventMouse* event = EventPressLeft::Instance();
    event->set(10, 100);
    assert(event->x() == 10 && event->y() == 100);

    event = EventPressRight::Instance();
    event->set(100, 10);
    assert(event->x() == 100 && event->y() == 10);

    event = EventReleaseLeft::Instance();
    event->set(100, 10);
    assert(event->x() == 100 && event->y() == 10);

    event = EventReleaseRight::Instance();
    event->set(100, 10);
    assert(event->x() == 100 && event->y() == 10);

    event = EventMouseDoubleClick::Instance();
    event->set(100, 10);
    assert(event->x() == 100 && event->y() == 10);

    event = EventMouseMove::Instance();
    event->set(100, 10);
    assert(event->x() == 100 && event->y() == 10);

    EventWheel* event1 = EventWheel::Instance();
    event1->set_angle(100);
    assert( event1->angle() == 100);
  }
};

} //namespace test
} //namespace tools

int main(){
  tools::test::Test().RunAllTest();
}
