#include "Map/BuildableTile.hpp"

BuildableTile::BuildableTile(float x, float y)
    : BaseTile(x, y, BaseTile::Buildable) {};

void BuildableTile::set_tower(std::shared_ptr<BaseTower> n_tower) {
  tower = n_tower;
}

void BuildableTile::remove_tower() { tower = nullptr; }

std::shared_ptr<BaseTower> BuildableTile::get_tower() const { return tower; }
