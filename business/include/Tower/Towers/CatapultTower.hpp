#pragma once

#include "Tower/BaseTower.hpp"
class CatapultTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 4;
  static constexpr unsigned PRICE = 100;
  static constexpr unsigned LEVELS = 3;

public:
  CatapultTower(std::shared_ptr<BaseTile> tile);
};
