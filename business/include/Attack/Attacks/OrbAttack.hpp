#pragma once

#include <array>
#include "Attack/BaseAttack.hpp"
class OrbAttack : public BaseAttack {
public:
  constexpr static std::array<int, 3> DAMAGE = {5, 10, 15};
  constexpr static std::array<int, 3> VELOCITY = {25, 25, 25};

public:
  OrbAttack(int level, float x, float y, float width, float height,
            Vector<float> target);
};
