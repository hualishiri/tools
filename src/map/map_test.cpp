#include "map/map.h"

#include "util/testharness.h"

namespace tools {

class MAP {};

TEST(MAP, GetSet) {
  Map* map = Map::Instance();
  map->set_zoom(12);
  map->set_origin_x(105);
  map->set_origin_y(112);

  ASSERT_EQ(map->zoom(), 12);
  ASSERT_EQ(map->origin_x(), 105);
  ASSERT_EQ(map->origin_y(), 112);
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
