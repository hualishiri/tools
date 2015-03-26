#include "opera/opera.h"

#include <iomanip>

#include "opera/opera_option.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class OPERA {};

TEST(OPERA, Iterator) {
  const int len = 4;
  double location_wgs[len] = {
    -87.65005229999997, 41.850033, 
    114.1223784, 22.3700556
  };

  tools::OperaOption::Track track;
  tools::OperaOption::Line line = {
    0x1428,
    location_wgs[0], location_wgs[1],
    location_wgs[2], location_wgs[3]
  };

  track.lines.push_back(line);
  track.types.push_back(tools::OperaOption::LINE);
  track.id = 0x14312;
  track.acceleration = 0;
  track.start_speed = 0.1;

  tools::OperaOption::Instance()->push_back_track(track);
  tools::OperaOption::Instance()->set_interval(1.0);

  Opera2D opera;
  tools::OperaOption::Instance()->ConvertToPixel();
  opera.Initialize(*(OperaOption::Instance()));
  Opera2D::Iterator iter(&opera);
  Opera2D::OperaState *opera_state = new Opera2D::OperaState();

  while(iter.Valid()) {
    iter.Value(*opera_state);
      opera_state->ConvertToWgs();
        for(std::size_t i = 0;
            i != opera_state->radar_set_state.radar_set_state.size();
            ++i) {
          LogDebug("radar id : %d",
              opera_state->radar_set_state.radar_set_state[i].id);
          for (std::size_t j = 0;
              j != opera_state
              ->radar_set_state.radar_set_state[i].targets.size();
              ++j)
            LogDebug(
                "object position : (%f, %f)",
                opera_state->radar_set_state.radar_set_state[i].targets[j].x,
                opera_state->radar_set_state.radar_set_state[i].targets[j].y);
        }

        for(std::size_t i = 0;
            i!= opera_state->track_set_state.track_set_state.size();
            ++i) {
          std::stringstream streamTemp;
          streamTemp << "updateObject("
              << opera_state->track_set_state.track_set_state[i].id
              << ", " << "0, "
              << std::setprecision(9)
              << opera_state->track_set_state.track_set_state[i].point.x
              << ", "
              << std::setprecision(9)
              << opera_state->track_set_state.track_set_state[i].point.y << ", "
              << opera_state->track_set_state.track_set_state[i].acc << ", "
              << opera_state->track_set_state.track_set_state[i].speed << ", "
              << opera_state->track_set_state.track_set_state[i].azimuth << ");";
            LogInfo("%s", streamTemp.str().c_str());
            streamTemp.clear();
        }
    iter.Next();
  }
  opera.Release();
}

} //namespace tools

int main(int argc, char** argv) {
  return tools::test::RunAllTests();
}
