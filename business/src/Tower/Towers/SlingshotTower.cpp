#include "Tower/Towers/SlingshotTower.hpp"
#include "Tower/BaseTower.hpp"

SlingshotTower::SlingshotTower(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, BaseTower::SlingshotTower, PRICE) {}
