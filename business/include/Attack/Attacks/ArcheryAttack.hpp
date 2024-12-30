#pragma once

#include "Attack/BaseAttack.hpp"
class ArcheryAttack : public BaseAttack {
public:
  static constexpr float DAMAGE = 1;
  static constexpr float VELOCITY = 30;

public:
  ArcheryAttack(float x, float y, float width, float height,
                Vector<float> target);
};
