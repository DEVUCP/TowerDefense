#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class CatapultAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {5, 10, 20};
  constexpr static std::array<int, 3> VELOCITY = {20, 20, 30};

public:
  CatapultAttack(int level, float x, float y, float width, float height,
                 Vector<float> target);
};
