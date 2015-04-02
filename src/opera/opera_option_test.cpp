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
      track.batch_count = 1;
      OperaOption::Line line = {0x123, 21.34, 34.12, 34.12, 43.34};
      track.lines.push_back(line);
      track.types.push_back(OperaOption::LINE);
      track.id = i;
      track.ids.push_back(i);
      opera_option.push_back_track(track);
    }
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
