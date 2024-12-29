#include "Tower/Towers/ArcheryTower.hpp"
#include "Tower/BaseTower.hpp"

ArcheryTower::ArcheryTower(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, BaseTower::ArcheryTower, PRICE) {}
