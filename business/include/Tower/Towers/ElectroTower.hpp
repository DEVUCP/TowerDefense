#pragma once

#include "Tower/BaseTower.hpp"
class ElectroTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;

public:
  ElectroTower(std::shared_ptr<BaseTile> tile);
};
