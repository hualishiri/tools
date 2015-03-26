#include "opera/opera.h"

#include <iomanip>

#include "map/map_projection.h"
#include "opera/opera_option.h"
#include "util/logger.h"
#include "util/testharness.h"

namespace tools {

class OPERA {};

TEST(OPERA, Iterator) {
  MapProjection::PixelPoint pixel_point;
  MapProjection::WgsPoint wgs_point;

  const int len = 4;
  double location_wgs[len] = {
    109.2350006, 34.0206885,
    114.1223784, 22.3700556
  };
  double location_pixel [len];

  for (int i=0 ; i!=len/2; ++i) {
    wgs_point.longitude = location_wgs[2*i];
    wgs_point.latitude = location_wgs[2*i+1];
    MapProjection::Instance(0)->FromWgsToPixel(wgs_point, pixel_point);
    location_pixel[2*i] = pixel_point.x;
    location_pixel[2*i+1] = pixel_point.y;
  }

  tools::OperaOption::Track track;
  tools::OperaOption::Line line = {
    0x1428,
    location_pixel[0], location_pixel[1],
    location_pixel[2], location_pixel[3]
  };

  for(int i = 0 ; i != len/2; ++i) {
    LogDebug("(%f, %f)", location_pixel[2*i], location_pixel[2*i+1]);
  }

  track.lines.push_back(line);
  track.types.push_back(tools::OperaOption::LINE);
  track.id = 0x14312;
  track.acceleration = 0;
  track.start_speed = 0.001;

  tools::OperaOption::Instance()->push_back_track(track);
  tools::OperaOption::Instance()->set_interval(1.0);

  Opera2D opera;
  opera.Initialize(*(OperaOption::Instance()));
  Opera2D::Iterator iter(&opera);
  Opera2D::OperaState *opera_state = new Opera2D::OperaState();

  while(iter.Valid()) {
    iter.Value(*opera_state);

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
          pixel_point.x = opera_state->track_set_state.track_set_state[i].point.x;
          pixel_point.y = opera_state->track_set_state.track_set_state[i].point.y;
          MapProjection::Instance(0)->FromPixelToWgs(pixel_point, wgs_point);

          std::stringstream streamTemp;
          streamTemp << "updateObject("
              << opera_state->track_set_state.track_set_state[i].id
              << ", " << "0, "
              << std::setprecision(9)
              //<< opera_state->track_set_state.track_set_state[i].point.x
              << wgs_point.longitude
              << ", "
              << std::setprecision(9)
              //<< opera_state->track_set_state.track_set_state[i].point.y << ", "
              << wgs_point.latitude
              << opera_state->track_set_state.track_set_state[i].acc << ", "
              << opera_state->track_set_state.track_set_state[i].speed << ", "
              << opera_state->track_set_state.track_set_state[i].azimuth << ");";
            LogDebug("%s", streamTemp.str().c_str());
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
