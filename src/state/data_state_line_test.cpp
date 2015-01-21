#define private public

#include "data_state_line.h"

#include <assert.h>

#include "util/tool.h"

namespace tools {
namespace test {

class Test {
public:
  int RunAllTest() {
    int sum = 0;
    return sum;
  }

  int TestDataStateLine() {
    DataStateLine data_state_line;
    assert(data_state_line.id() == 0);
    assert(DoubleEqual(0.0, data_state_line.start_x()));
    assert(DoubleEqual(0.0, data_state_line.start_y()));
    assert(DoubleEqual(0.0, data_state_line.move_x()));
    assert(DoubleEqual(0.0, data_state_line.move_y()));

    double data[] = { 43.34, 12.53, 78.12, 98.11 };
    int id = 89321;
    data_state_line.set_id(id);
    data_state_line.set_start(data[0], data[1]);
    data_state_line.set_move(data[2], data[3]);
    assert(id == data_state_line.id());
    assert(DoubleEqual(data_state_line.start_x(), data[0]));
    assert(DoubleEqual(data_state_line.start_y(), data[1]));
    assert(DoubleEqual(data_state_line.move_x(), data[2]));
    assert(DoubleEqual(data_state_line.move_y(), data[3]));
    return 0;
  }
};

} //namespace test
} //namespace tools``

int main() {
  return tools::test::Test().RunAllTest();
}
