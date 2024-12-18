
#pragma once

#include "Map/BaseTile.hpp"
class NonBuildableTile : public BaseTile {
public:
  NonBuildableTile() : BaseTile(NonBuildable) {};
private:
};
