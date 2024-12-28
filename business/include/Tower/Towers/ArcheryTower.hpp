#pragma once

#include "Tower/BaseTower.hpp"
class ArcheryTower : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;

public:
  ArcheryTower(std::shared_ptr<BaseTile> tile);
};
