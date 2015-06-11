#include "track.h"

#include <vector>

#include "opera/acceleration.h"
#include "opera/shape.h"
#include "opera/line.h"
#include "opera/circle.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class TRACK {};

TEST(TRACK, Iterator) {
  float interval = 1.0*0.1;
  float init_speed = 0.00026997840172*10000;
  int i=0;
  Shape2D* line = new Line2D(Point2D(0.789872, 0.721040));
  Shape2D* circle = new Circle2D(Point2D(0.789872, 0.721040), 3.1415);
  Acceleration* acc_uniform = new UniformAcceleration();
  Acceleration* acc_constant = new ConstantAcceleration(0.00001);
  Track2D::TrackUnitSet* track_unit_set = new Track2D::TrackUnitSet();

  std::vector<TrackUnit*> track_units;
  TrackUnit* track_unit = NULL;

  track_unit = new TrackUnit(line, acc_uniform, interval, init_speed);
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_constant,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_uniform,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_constant,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_uniform,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_constant,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_uniform,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_constant,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  track_unit = new TrackUnit(line,
                             acc_uniform,
                             interval,
                             (*track_unit_set)[i++]->GetEndSpeed());
  track_units.push_back(track_unit);
  track_unit_set->push_back(track_unit);

  Track2D track(0x01, track_unit_set, interval, init_speed);
  Track2D::Iterator iter(&track);
  Track2D::TrackState track_state;
  while(iter.Valid()){
    iter.Value(track_state);
    iter.Next();
  }

  delete line;
  delete circle;
  delete acc_uniform;
  delete acc_constant;
  delete track_unit_set;
  for (std::size_t i=0; i!=track_units.size(); ++i)
    delete track_units[i];
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
