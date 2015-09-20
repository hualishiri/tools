#ifndef TOOLS_OPERA_OPERA_H_
#define TOOLS_OPERA_OPERA_H_

#include <iostream>

#include "opera/algo_fusion.h"
#include "opera/opera_option.h"
#include "opera/radar_set.h"
#include "opera/radar_sector.h"
#include "opera/track_set.h"
#include "opera/opera_analysis.h"

namespace tools {

class Opera2D {
 public:
  struct OperaState {
    friend std::ostream& operator<<(std::ostream& out,
                                    const OperaState& opera_state);
    friend std::istream& operator>>(std::istream& in, OperaState& opera_state);
    void ConvertToWgs();
    void ConvertToWgs(void (*)(double*, double*));

    TrackSet2D::TrackSetState track_set_state;
    RadarSet2D::RadarSetState radar_set_state;

    std::vector<AlgoFusion::FusionTarget> fusion_set_state;
  };

  class Iterator {
   public:
    Iterator(Opera2D* opera);
    Iterator(const Iterator& iterator);
    Iterator& operator=(const Iterator& iterator);
    ~Iterator();
    bool Valid() const;
    void Next();
    void Value(OperaState& opera_state);
    void Reset();

   private:
    void ChangeRadarPosition(OperaState& opera_state);

    Opera2D* opera_;
    TrackSet2D::Iterator *iter_track_set_;
  }; 

  struct Garbage {
    std::vector<RadarSet2D::RadarSet*> garbage_radar_set2d_radar_sets;
    std::vector<SectorRadar::Radar*> garbage_sector_radar_radars;
    std::vector<RadarNoise*> garbage_radar_noises;
    std::vector<SectorRadar*> garbage_sector_radars;
    std::vector<TrackSet2D::TrackSet*> garbage_track_set2d_track_sets;
    std::vector<TrackSet2D::TrackSetPosition*> 
        garbage_track_set2d_track_set_positions;
    std::vector<TrackSet2D::TrackSetDelay*> garbage_track_set2d_track_set_delays;
    std::vector<Track2D::TrackUnitSet*> garbage_track2d_track_unit_sets;
    std::vector<Point2D*> garbage_points;
    std::vector<Shape2D*> garbage_shapes;
    std::vector<Acceleration*> garbage_accelerations;
    std::vector<TrackUnit*> garbage_track_units;
    std::vector<Track2D*> garbage_track2ds;
  };

  Opera2D() : track_set_(0), radar_set_(0) {}
  Opera2D(TrackSet2D* track_set, RadarSet2D* radar_set)
    : track_set_(track_set), radar_set_(radar_set) {
  }

  long long GetSumTick() const;
  void Initialize(const OperaOption& opera_option);
  void Release();

 private:
  void BuildRadar(const OperaOption& opera_option);
  void BuildTrack(const OperaOption& opera_option);

  TrackSet2D* track_set_;
  RadarSet2D* radar_set_;

  Garbage garbage_;

  friend class Iterator;
};

std::ostream& operator<<(std::ostream& out,
                         const Opera2D::OperaState& opera_state);
std::istream& operator>>(std::istream& in, Opera2D::OperaState& opera_state);

} //namespace tools

#endif //TOOLS_OPERA_OPERA_H_
