#include "event/event.h"

#include "util/testharness.h"

namespace tools {

class EVENT {};

TEST(EVENT, Instance) {
  ASSERT_EQ(EventMousePressLeft::Instance(),
            EventMousePressLeft::Instance());
  ASSERT_EQ(EventMousePressRight::Instance(),
            EventMousePressRight::Instance());
  ASSERT_EQ(EventMouseReleaseLeft::Instance(),
            EventMouseReleaseLeft::Instance());
  ASSERT_EQ(EventMouseReleaseRight::Instance(),
            EventMouseReleaseRight::Instance());
  ASSERT_EQ(EventMouseDoubleClick::Instance(),
            EventMouseDoubleClick::Instance());
  ASSERT_EQ(EventMouseMove::Instance(),
            EventMouseMove::Instance());
  ASSERT_EQ(EventButtonPointer::Instance(),
            EventButtonPointer::Instance());
  ASSERT_EQ(EventButtonLine::Instance(),
            EventButtonLine::Instance());
  ASSERT_EQ(EventButtonCircle::Instance(),
            EventButtonCircle::Instance());
  ASSERT_EQ(EventButtonEclipse::Instance(),
            EventButtonEclipse::Instance());

  ASSERT_EQ(EventButtonStart::Instance(),
            EventButtonStart::Instance());
  ASSERT_EQ(EventButtonPause::Instance(),
            EventButtonPause::Instance());
  ASSERT_EQ(EventButtonStep::Instance(),
            EventButtonStep::Instance());
  ASSERT_EQ(EventButtonStop::Instance(),
            EventButtonStop::Instance());

  ASSERT_EQ(EventButtonRadar::Instance(),
            EventButtonRadar::Instance());
}

} //namespace tools

int main(int argc, char**argv) {
  return tools::test::RunAllTests();
}
