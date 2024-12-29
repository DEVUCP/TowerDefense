#include "Tower/Towers/ElectroTower.hpp"
#include "Tower/BaseTower.hpp"

ElectroTower::ElectroTower(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, BaseTower::ElectroTower) {}
