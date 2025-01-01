#include "Attack/Attacks/CrossbowAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

CrossbowAttack::CrossbowAttack(int level, float x, float y, float width,
                               float height, Vector<float> target)
    : BaseAttack(x, y, width, height, VELOCITY[level], target, DAMAGE[level],
                 BaseAttack::CROSSBOW_ATTACK),
      Positionable(x, y) {}
