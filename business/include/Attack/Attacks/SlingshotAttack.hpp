#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class SlingshotAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {9, 18, 27};
  constexpr static std::array<int, 3> VELOCITY = {30, 30, 30};

public:
  SlingshotAttack(int level, float x, float y, float width, float height,
                  Vector<float> target);
};
