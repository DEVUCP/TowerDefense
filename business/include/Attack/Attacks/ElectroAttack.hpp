#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class ElectroAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {2, 4, 6};
  constexpr static std::array<int, 3> VELOCITY = {30, 30, 30};

public:
  ElectroAttack(int level, float x, float y, float width, float height,
                Vector<float> target);
};
