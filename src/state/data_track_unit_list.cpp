#include "data_track_unit_list.h"

#include <assert.h>

#include "state/opera_option.h"
#include "util/tool.h"

namespace tools {

DataTrackUnitList* DataTrackUnitList::Instance() {
  if (!data_) data_ = new DataTrackUnitList();
  return data_;
}

void DataTrackUnitList::push_back_line(long long id,
                                       double end_x,
                                       double end_y) {
  units_id_.push_back(id);
  units_flag_.push_back(LINE);
  units_.push_back(end_x);
  units_.push_back(end_y);
}

void DataTrackUnitList::push_back_circle(long long id,
                                         double center_x,
                                         double center_y,
                                         double side_x,
                                         double side_y, 
                                         double angle_x,
                                         double angle_y) {
  units_id_.push_back(id);
  units_flag_.push_back(CIRCLE);
  units_.push_back(center_x);
  units_.push_back(center_y);
  units_.push_back(side_x);
  units_.push_back(side_y);
  units_.push_back(angle_x);
  units_.push_back(angle_y);
}

void DataTrackUnitList::push_back_eclipse(long long id, 
                                          double center_x,
                                          double center_y,
                                          double end_x,
                                          double end_y,
                                          double side_x,
                                          double side_y,
                                          double angle_x,
                                          double angle_y) {
  units_id_.push_back(id);
  units_flag_.push_back(ECLIPSE);
  units_.push_back(center_x);
  units_.push_back(center_y);
  units_.push_back(end_x);
  units_.push_back(end_y);
  units_.push_back(side_x);
  units_.push_back(side_y);
  units_.push_back(angle_x);
  units_.push_back(angle_y);
}

OperaOption::Track DataTrackUnitList::track() const {
  assert(id_ != 0);
  OperaOption::Track track;
  track.id = id_;
  track.id = GenerateId();
  int index = 0;
  if (units_flag_[0] == LINE) {
    OperaOption::Line line = {
      units_id_[0],
      start_x_,
      start_y_,
      units_[0],
      units_[1]
    };
    index += 2;
    track.lines.push_back(line);
    track.types.push_back(OperaOption::LINE);
  } else if (units_flag_[0] == CIRCLE) {
    OperaOption::Circle circle = {
      units_id_[0],
      start_x_,
      start_y_,
      units_[0],
      units_[1],
      units_[2],
      units_[3],
      units_[4],
      units_[5]
    };
    index += 6;
  } else if (units_flag_[0] == ECLIPSE) {
    OperaOption::Eclipse eclipse = { 
      units_id_[0],
      start_x_,
      start_y_,
      units_[0],
      units_[1],
      units_[2],
      units_[3],
      units_[4],
      units_[5],
      units_[6],
      units_[7]
    };
    index += 8;
  }
  for (int i = 1; i != units_id_.size(); ++i) {
    if (units_flag_[i] == LINE) {
      OperaOption::Line line = {
        units_id_[i],
        units_[index-2],
        units_[index-1],
        units_[index],
        units_[index+1]
      };
      index += 2;
      track.lines.push_back(line);
      track.types.push_back(OperaOption::LINE);
    } else if (units_flag_[i] == CIRCLE) {
      OperaOption::Circle circle = { 
        units_id_[i],
        units_[index-2],
        units_[index-1],
        units_[index],
        units_[index+1],
        units_[index+2],
        units_[index+3],
        units_[index+4],
        units_[index+5]
      };
      index += 6;
      track.circles.push_back(circle);
      track.types.push_back(OperaOption::CIRCLE);
    } else if (units_flag_[i] == ECLIPSE) {
      OperaOption::Eclipse eclipse = { 
        units_id_[i],
        units_[index-2],
        units_[index-1],
        units_[index],
        units_[index+1],
        units_[index+2],
        units_[index+3],
        units_[index+4],
        units_[index+5],
        units_[index+6],
        units_[index+7]
      };
      index += 8;
      track.eclipses.push_back(eclipse);
      track.types.push_back(OperaOption::ECLIPSE);
    }
  } 
  return track;
}

DataTrackUnitList* DataTrackUnitList::data_ = 0;

} //namespace tools
