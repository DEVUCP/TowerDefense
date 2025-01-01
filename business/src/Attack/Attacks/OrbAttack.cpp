#include "Attack/Attacks/OrbAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

OrbAttack::OrbAttack(int level, float x, float y, float width, float height,
                     Vector<float> target)
    : BaseAttack(level, x, y, width, height, VELOCITY[level - 1], target,
                 DAMAGE[level - 1], BaseAttack::ORB_ATTACK),
      Positionable(x, y) {}
