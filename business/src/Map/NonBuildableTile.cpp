#include "Map/NonBuildableTile.hpp"
#include "Map/BaseTile.hpp"

NonBuildableTile::NonBuildableTile(float x, float y)
    : BaseTile(x, y, NonBuildable) {}
