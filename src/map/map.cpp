#include "map.h"

namespace tools{

Map* Map::map_ = 0;

Map* Map::Instance(){
  if(!map_) map_ = new Map();
  return map_;
}

} //namespace tools
