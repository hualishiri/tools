#ifndef OPERA_H_
#define OPERA_H_

#include <vector>

#include "track.h"
#include "target.h"
#include "sensor.h"

namespace tools{

struct OperaOption{
  unsigned int kInternal;
  std::vector<Track*> *tracks;
  std::vector<Target*> *targets;
  std::vector<TargetState*> *target_init_states;
  std::vector<Sensor*> *sensors;
  std::vector<SensorState*> *sensor_states;
};

struct OperaState{
  std::vector<TargetState*> *target_states;
  std::vector<SensorState*> *sensor_states;
};

class Opera{
public:
  virtual void Initialize(OperaOption* option)  = 0;
  virtual bool Valid() = 0;
  virtual void Next() = 0;
  virtual void GetState(OperaState* state) = 0;
  virtual void Finalize() = 0;
  virtual unsigned long GetSumTime() const = 0;
};

class OperaWar : public Opera{
public:
  virtual bool Valid();
  virtual void Next();

private:
  OperaOption* option_;
  unsigned int time_current_;
  unsigned int time_sum_;
};

} //namespace tools

#endif //OPERA_H_
