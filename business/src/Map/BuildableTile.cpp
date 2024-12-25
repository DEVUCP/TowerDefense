#include "Map/BuildableTile.hpp"

BuildableTile::BuildableTile(float x, float y)
    : BaseTile(x, y, BaseTile::Buildable) {};

// void BuildableTile::set_tower(std::shared_ptr<BaseTower> tower) {}
//
// void BuildableTile::remove_tower() {}
//
// std::shared_ptr<BaseTower> BuildableTile::get_tower() const { return tower; }
