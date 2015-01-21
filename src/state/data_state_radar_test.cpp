#define private public

#include "state/data_state_radar.h"
#include "util/tool.h"

#include <assert.h>

namespace tools {
namespace test {

class Test {
 public:
  int RunAllTest() {
    int sum = 0;
    sum += TestDataStateRadar();
    return sum;
  }

  int TestDataStateRadar() {
    DataStateRadar data_state_radar;
    assert(0 == data_state_radar.id());
    assert(0 == data_state_radar.id());
    assert(DoubleEqual(data_state_radar.center_x(), 0.0));
    assert(DoubleEqual(data_state_radar.center_y(), 0.0));
    assert(DoubleEqual(data_state_radar.move_x(), 0.0));
    assert(DoubleEqual(data_state_radar.move_y(), 0.0));

    double data[] = { 32.45, 72.85, 14.85, 27.16 };
    int id = 1111;
    data_state_radar.set_center(data[0], data[1]);
    data_state_radar.set_move(data[2], data[3]);
    data_state_radar.set_id(id);
    assert(id == data_state_radar.id());
    assert(DoubleEqual(data_state_radar.center_x(), data[0]));
    assert(DoubleEqual(data_state_radar.center_y(), data[1]));
    assert(DoubleEqual(data_state_radar.move_x(), data[2]));
    assert(DoubleEqual(data_state_radar.move_y(), data[3]));
    return 0;
  }
};

} //namespace test
} //namespace tools

int main() {
  return tools::test::Test().RunAllTest();
}
