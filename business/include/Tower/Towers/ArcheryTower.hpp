#pragma once

#include "Tower/BaseTower.hpp"
class ArcheryTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 2;
  static constexpr unsigned PRICE = 100;
  static constexpr unsigned LEVELS = 3;

public:
  ArcheryTower(std::shared_ptr<BaseTile> tile);
};
