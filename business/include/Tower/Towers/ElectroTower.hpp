#pragma once

#include "Tower/BaseTower.hpp"
class ElectroTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 2;
  static constexpr unsigned PRICE = 50;
  static constexpr unsigned LEVELS = 3;

public:
  ElectroTower(std::shared_ptr<BaseTile> tile);
};
