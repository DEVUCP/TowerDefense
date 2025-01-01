#pragma once

#include "Tower/BaseTower.hpp"
class OrbTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;
  static constexpr unsigned PRICE = 150;
  static constexpr unsigned LEVELS = 3;

public:
  OrbTower(std::shared_ptr<BaseTile> tile);
};
