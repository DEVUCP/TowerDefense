#include "Attack/Attacks/CatapultAttack.hpp"
#include <iostream>
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

CatapultAttack::CatapultAttack(int level, float x, float y, float width,
                               float height, Vector<float> target)
    : BaseAttack(level, x, y, width, height, VELOCITY[level - 1], target,
                 DAMAGE[level - 1], BaseAttack::CATAPULT_ATTACK),
      Positionable(x, y) {}
