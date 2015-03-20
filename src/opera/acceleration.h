#ifndef TOOLS_OPERA_ACCELERATION_H_
#define TOOLS_OPERA_ACCELERATION_H_

namespace tools {

class Acceleration {
 public:
   virtual ~Acceleration() {}
   virtual float GetAcceleration(long time) const = 0;
};

class UniformAcceleration : public Acceleration {
 public:
  float GetAcceleration(long time) const { return 0.0; }
};

class ConstantAcceleration : public Acceleration {
 public:
  explicit ConstantAcceleration(float acc) : acc_(acc) {}
  float GetAcceleration(long time) const { return acc_; }

 private:
  const float acc_; 
};

class VariableAcceleration : public Acceleration {
 public:
  explicit VariableAcceleration(float (*func)(long)) : acc_(func) {}
  float GetAcceleration(long time) const { return acc_(time); }

 private:
  float (*acc_)(long);
};

} //namespace tools

#endif //TOOLS_OPERA_ACCELERATION_H_
