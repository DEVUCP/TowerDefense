#include "Attack/Attacks/CatapultAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

CatapultAttack::CatapultAttack(int level, float x, float y, float width,
                               float height, Vector<float> target)
    : BaseAttack(x, y, width, height, VELOCITY[level], target, DAMAGE[level],
                 BaseAttack::CATAPULT_ATTACK),
      Positionable(x, y) {}
