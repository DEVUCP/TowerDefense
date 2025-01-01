#pragma once

#include "Tower/BaseTower.hpp"
class OrbTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;
  static constexpr unsigned PRICE = 25;

public:
  OrbTower(std::shared_ptr<BaseTile> tile);
};
