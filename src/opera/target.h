#ifndef TOOLS_TARGET_H_
#define TOOLS_TARGET_H_

#include "track.h"

#include <vector>

namespace tools{

struct TargetState{};

struct TargetOption{
  unsigned int kInternal;
  std::vector<Track*> *tracks;
  std::vector<TargetState*> *target_states;
};

class Target{
public:
  virtual void Initialize(TargetOption* option) = 0;
  virtual bool Valid() const = 0;
  virtual void Next() = 0;
  virtual void Reset() = 0;
  virtual void GetState(TargetState* state) = 0;
  virtual unsigned long GetSumTime() const;
};


class AirTarget : public Target{
public:
  virtual void Initialize(TargetOption* option);
  virtual bool Valid() const;
  virtual void Next();
  virtual void Reset();
  virtual void GetState(TargetState* state);
  virtual unsigned long GetSumTime() const;
private:
  TargetOption* option_;
  unsigned long time_current_;
  unsigned long time_sum_;
};

class LandTarget : public Target{
public:
  virtual void Initialize(TargetOption* option);
  virtual bool Valid() const;
  virtual void Next();
  virtual void Reset();
  virtual void GetState(TargetState* state);
  virtual unsigned long GetSumTime() const;
private:
  TargetOption* option_;
  unsigned long time_current_;
  unsigned long time_sum_;
};

class SurfaceSeaTarget : public Target{
public:
  virtual void Initialize(TargetOption* option);
  virtual bool Valid() const;
  virtual void Next();
  virtual void Reset();
  virtual void GetState(TargetState* state);
  virtual unsigned long GetSumTime() const;
private:
  TargetOption* option_;
  unsigned long time_current_;
  unsigned long time_sum_;
};


class UnderSeaTarget : public Target{
public:
  virtual void Initialize(TargetOption* option);
  virtual bool Valid() const;
  virtual void Next();
  virtual void Reset();
  virtual void GetState(TargetState* state);
  virtual unsigned long GetSumTime() const;
private:
  TargetOption* option_;
  unsigned long time_current_;
  unsigned long time_sum_;
};

} //namespace tools
#endif //TOOLS_TARGET_H_
