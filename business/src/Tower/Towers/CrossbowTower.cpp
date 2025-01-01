#include "Tower/Towers/CrossbowTower.hpp"
#include "Tower/BaseTower.hpp"

CrossbowTower::CrossbowTower(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, BaseTower::CrossbowTower, PRICE) {}
