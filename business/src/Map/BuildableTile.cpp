#include "Map/BuildableTile.hpp"

BuildableTile::BuildableTile() : BaseTile(BaseTile::Buildable) {};

void BuildableTile::set_tower(std::shared_ptr<BaseTower> tower) {}

void BuildableTile::remove_tower() {}
