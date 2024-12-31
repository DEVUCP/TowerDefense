#pragma once

#include "Tower/BaseTower.hpp"
class ArcheryTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;
  static constexpr unsigned PRICE = 25;
  static constexpr unsigned LEVELS = 3;

public:
  ArcheryTower(std::shared_ptr<BaseTile> tile);
};
