#include "tool.h"

namespace tools{

namespace{
long long id = 0xdeedbeef;
}

long long GenerateId(){
  ++id;
  return id;
}

double ConvertFromXTo(int zoom, int x);
double ConvertFromYToLatitude(int zoom, int y);
int ConvertLongitudeToX(int zoom , double longitude);
int ConvertLatitudeToY();

} //namespace tools
