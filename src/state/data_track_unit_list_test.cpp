#define private public

#include "data_track_unit_list.h"

#include <assert.h>

#include "util/tool.h"

namespace tools {
namespace test {

class Test {
 public:
  int RunAllTest() {
    int sum = 0;
    sum += TestDataTrackUnitList();
    return sum;
  }

  int TestDataTrackUnitList() {
    DataTrackUnitList data_track_unit_list;
    assert(DoubleEqual(data_track_unit_list.start_x_, 0.0));
    assert(DoubleEqual(data_track_unit_list.start_y_, 0.0));
    assert(data_track_unit_list.units_.size() == 0);
    assert(data_track_unit_list.units_id_.size() == 0);
    assert(data_track_unit_list.units_flag_.size() == 0);

    data_track_unit_list.set_start(43.1341, 98.31241);
    double data[] = {
      43.12, 12.43, 89.12, 18.123,
      47.413, 52.16, 41.16, 54.34,
      51.36, 16.34, 57.12, 67.82,
      41.64, 91.31, 92.52, 51.23,
      73.23, 98.12, 39.21
    };
    long long ids[] = { 9841, 9843, 2198 };
    long long track_id = 1414731;

    data_track_unit_list.set_id(track_id);
    assert(track_id == data_track_unit_list.id_);
    
    int index = 0;
    int id_index = 0;
    data_track_unit_list.set_start(data[index], data[index+1]);
    index += 2;
    data_track_unit_list.push_back_line(ids[id_index], 
                                        data[index],
                                        data[index+1]);
    index += 2;
    ++id_index;
    data_track_unit_list.push_back_circle(ids[id_index], 
                                          data[index],
                                          data[index+1],
                                          data[index+2],
                                          data[index+3], 
                                          data[index+4],
                                          data[index+5]);
    ++id_index;
    index += 6;
    data_track_unit_list.push_back_eclipse(ids[id_index], 
                                           data[index],
                                           data[index+1],
                                           data[index+2],
                                           data[index+3], 
                                           data[index+4],
                                           data[index+5],
                                           data[index+6],
                                           data[index+7]);
    index += 8;
 
    for (int i = 0; i != data_track_unit_list.units_id_.size(); ++i)
      assert(data_track_unit_list.units_id_[i] == ids[i]);   
    assert(DoubleEqual(data[0], data_track_unit_list.start_x_));
    assert(DoubleEqual(data[1], data_track_unit_list.start_y_));
    for (int i = 0; i != data_track_unit_list.units_.size(); ++i) {
      double lhs = data[i+2];
      double rhs = data_track_unit_list.units_[i];
      assert(DoubleEqual(data[i+2], data_track_unit_list.units_[i]));
    }
    assert(data_track_unit_list.units_flag_[0] == DataTrackUnitList::LINE);
    assert(data_track_unit_list.units_flag_[1] == DataTrackUnitList::CIRCLE);
    assert(data_track_unit_list.units_flag_[2] == DataTrackUnitList::ECLIPSE);

    OperaOption::Track track = data_track_unit_list.track();
    assert(track.types[0] == OperaOption::LINE);
    assert(track.types[1] == OperaOption::CIRCLE);
    assert(track.types[2] == OperaOption::ECLIPSE);
    assert(track.lines[0].id == ids[0]);
    assert(track.circles[0].id == ids[1]);
    assert(track.eclipses[0].id == ids[2]);
    assert(DoubleEqual(track.lines[0].start_x, data[0]));
    assert(DoubleEqual(track.lines[0].start_y, data[1]));
    assert(DoubleEqual(track.lines[0].end_x, data[2]));
    assert(DoubleEqual(track.lines[0].end_y, data[3]));
    assert(DoubleEqual(track.circles[0].start_x, data[2]));
    assert(DoubleEqual(track.circles[0].start_y, data[3]));
    assert(DoubleEqual(track.circles[0].center_x, data[4]));
    assert(DoubleEqual(track.circles[0].center_y, data[5]));
    assert(DoubleEqual(track.circles[0].side_x, data[6]));
    assert(DoubleEqual(track.circles[0].side_y, data[7]));
    assert(DoubleEqual(track.circles[0].angle_x, data[8]));
    assert(DoubleEqual(track.circles[0].angle_y, data[9]));
    assert(DoubleEqual(track.eclipses[0].start_x, data[8]));
    assert(DoubleEqual(track.eclipses[0].start_y, data[9]));
    assert(DoubleEqual(track.eclipses[0].center_x, data[10]));
    assert(DoubleEqual(track.eclipses[0].center_y, data[11]));
    assert(DoubleEqual(track.eclipses[0].end_x, data[12]));
    assert(DoubleEqual(track.eclipses[0].end_y, data[13]));
    assert(DoubleEqual(track.eclipses[0].side_x, data[14]));
    assert(DoubleEqual(track.eclipses[0].side_y, data[15]));
    assert(DoubleEqual(track.eclipses[0].angle_x, data[16]));
    assert(DoubleEqual(track.eclipses[0].angle_y, data[17]));
    return 0;
  }
};

} //namespace test
} //namespace tools

int main() {
  return tools::test::Test().RunAllTest();
}
