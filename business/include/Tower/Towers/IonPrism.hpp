#pragma once

#include "Tower/BaseTower.hpp"
class IonPrism : public BaseTower {
public:
  static constexpr unsigned RANGE = 1;
  static constexpr unsigned ATTACK_SPEED = 1;
  static constexpr unsigned ATTACK_DAMAGE = 1;

public:
  IonPrism(int i, int j);
};
