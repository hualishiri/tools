#ifndef TOOLS_UTIL_TOOL_H_
#define TOOLS_UTIL_TOOL_H_

namespace tools {

extern const double kRadius;
extern const double T_PI;

long long GenerateId();

void SetId(long long id_in);

bool DoubleEqual(double lhs, double rhs);

double AngleInCircle(double x, double y);

double AngleFromStartByClockInCircle(double start_x,
                                     double start_y,
                                     double center_x,
                                     double center_y,
                                     double angle_x,
                                     double angle_y);

void FromWgsToPixel(double* longitude, double* latitude);
void FromPixelToWgs(double* x, double* y);

double GetRandNumber(int seed);

double Radius(double angle);

double Distance2D(double lhs_x, double lhs_y, double rhs_x, double rhs_y);

double Distance2DArc(double lhs_x, double lhs_y, double rhs_x, double rhs_y);

} //namespace tools

#endif //TOOLS_UTIL_TOOL_H_
