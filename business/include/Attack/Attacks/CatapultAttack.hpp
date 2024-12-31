#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class CatapultAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {4, 6, 8};
  constexpr static std::array<int, 3> VELOCITY = {35, 45, 60};

public:
  CatapultAttack(int level, float x, float y, float width, float height,
                 Vector<float> target);
};
