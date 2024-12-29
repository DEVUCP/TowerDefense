#pragma once

#include "Tower/BaseTower.hpp"
class SlingshotTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;

public:
  SlingshotTower(std::shared_ptr<BaseTile> tile);
};
