#include "map.h"

namespace tools {

Map* Map::Instance() {
  if (!map_) map_ = new Map();
  return map_;
}

Map* Map::map_ = 0;

} //namespace tools
