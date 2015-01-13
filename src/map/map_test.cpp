#include "map.h"

#include <cassert>

namespace tools{
namespace test{
class Test{
public:
  void RunAllTest(){
    TestMap();
  }

  void TestMap(){
    Map* map = Map::Instance();
    map->set_zoom(12);
    assert(map->zoom() == 12);
    map->set_origin_x(100);
    assert(map->origin_x() == 100);
    map->set_origin_y(102);
    assert(map->origin_y() == 102);
    map->move(14, 18);
    assert(map->origin_x());
  }
};

}
}

int main(){
  
  return 0;
}
