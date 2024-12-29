#include "Tower/Towers/CatapultTower.hpp"
#include "Tower/BaseTower.hpp"

CatapultTower::CatapultTower(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, BaseTower::CatapultTower, PRICE) {}
