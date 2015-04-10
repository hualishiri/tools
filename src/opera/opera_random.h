#ifndef TOOLS_OPERA_OPERA_RANDOM_H_
#define TOOLS_OPERA_OPERA_RANDOM_H_

#include <stack>
#include <vector>

namespace tools {

class OperaRandom {
 public:
  enum TrackUnitType {LINE, CIRCLE};

  struct OperaRandomParameter {
    double rectangle_up_x;
    double rectangle_up_y;
    double rectangle_down_x;
    double rectangle_down_y;
    int radar_number_min;
    int radar_number_max;
    double radar_radius_min;
    double radar_radius_max;
    int track_number_min;
    int track_number_max;
    int track_unit_number_min;
    int track_unit_number_max;
  };

  struct Radar {
    double center_x;
    double center_y;
    double radius;
  };

  struct Line {
    double start_x;
    double start_y;
    double end_x;
    double end_y;
  };

  struct Circle {
    double start_x;
    double start_y;
    double center_x;
    double center_y;
    double angle;
  };

  struct Track {
    std::vector<Line> lines;
    std::vector<Circle> circles;
    std::vector<TrackUnitType> types;
  };


  struct RandomOpera{
    std::vector<Radar> radars;
    std::vector<Track> tracks;
  };

  OperaRandom(const OperaRandomParameter& opera_random_para) 
    : opera_random_para_(opera_random_para) {
  }

  void GetResult(RandomOpera &random_opera) const;

  void SetOperaRandomParameter(const OperaRandomParameter& opera_random_para) {
    opera_random_para_ = opera_random_para;
  }

 //private:
  Radar GetRadar(int seed) const;
  int GetRadarNumber(int seed) const;
  int GetTrackNumber(int seed) const;
  Track GetTrack(int seed) const;
  bool ParameterValid() const;
  bool RangeValid(int min, int max) const;
  bool RangeValid(double min, double max) const;
  double GetNumber(double min, double max, int seed) const;
  void GetRandomPosition(double &x, double &y, int seed) const;
  void GetRandomPositionSet(std::stack<std::pair<double, double> > &position,
                            int n,
                            int seed) const;
  void GetRandomPositionOrder(std::stack<int> &pos_order,
                              int track_unit_number,
                              int line_number,
                              int seed) const;
  void GetRandomAngle(std::stack<double> &angles, int n, int seed) const;
  void GetArcEndPoint(const Circle& circle, double &x, double &y) const;

  OperaRandomParameter opera_random_para_;
};

} //namespace tools

#endif //TOOLS_OPERA_OPERA_RANDOM_H_