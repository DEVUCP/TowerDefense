#include "Tower/Towers/OrbTower.hpp"
#include "Tower/BaseTower.hpp"

OrbTower::OrbTower(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, BaseTower::OrbTower, PRICE) {}
