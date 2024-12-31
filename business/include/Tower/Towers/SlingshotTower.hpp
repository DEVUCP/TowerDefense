#pragma once

#include "Tower/BaseTower.hpp"
class SlingshotTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 3;
  static constexpr unsigned PRICE = 100;
  static constexpr unsigned LEVELS = 3;

public:
  SlingshotTower(std::shared_ptr<BaseTile> tile);
};
