#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class CrossbowAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {10, 20, 30};
  constexpr static std::array<int, 3> VELOCITY = {20, 20, 30};

public:
  CrossbowAttack(int level, float x, float y, float width, float height,
                 Vector<float> target);
};
