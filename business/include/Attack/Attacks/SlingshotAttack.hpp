#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class SlingshotAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {1, 2, 4};
  constexpr static std::array<int, 3> VELOCITY = {20, 20, 20};

public:
  SlingshotAttack(int level, float x, float y, float width, float height,
                  Vector<float> target);
};
