#include "opera/opera_option.h"

#include "util/testharness.h"

namespace tools {

class OPERAOPTION {};

TEST(OPERAOPTION, PushBack) {
  OperaOption opera_option;
    for (int i = 1; i != 10; ++i) {
      OperaOption::Radar radar;
      radar.id = i;
      opera_option.push_back_radar(radar);
    }
    opera_option.pop_radar(2);
    ASSERT_TRUE(opera_option.size_radar() == 8);
    opera_option.pop_radar(15);
    ASSERT_TRUE(opera_option.size_radar() == 8);

    for (int i = 1; i != 10; ++i) {
      OperaOption::Object object;
      object.id = i;
      opera_option.push_back_object(object);
    }
    opera_option.pop_object(2);
    ASSERT_TRUE(opera_option.size_object() == 8);
    opera_option.pop_object(15);
    ASSERT_TRUE(opera_option.size_object() == 8);
    for (int i = 1; i != 10; ++i) {
      OperaOption::Track track;
      track.id = i;
      opera_option.push_back_track(track);
    }
    opera_option.pop_track(2);
    ASSERT_TRUE(opera_option.size_track() == 8);
    opera_option.pop_track(15);
    ASSERT_TRUE(opera_option.size_track() == 8);
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
