#pragma once

#include "Tower/BaseTower.hpp"
class CrossbowTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;
  static constexpr unsigned PRICE = 10;
  static constexpr unsigned LEVELS = 3;

public:
  CrossbowTower(std::shared_ptr<BaseTile> tile);
};
