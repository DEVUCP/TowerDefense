#pragma once

#include "Tower/BaseTower.hpp"
class CatapultTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 3;

public:
  CatapultTower(std::shared_ptr<BaseTile> tile);
};
