#pragma once

#include <memory>
#include "Tower/BaseTower.hpp"
class IonPrism : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;
  static constexpr unsigned PRICE = 50;

public:
  IonPrism(std::shared_ptr<BaseTile> tile);
};
