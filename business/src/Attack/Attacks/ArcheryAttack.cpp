#include "Attack/Attacks/ArcheryAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

ArcheryAttack::ArcheryAttack(int level, float x, float y, float width,
                             float height, Vector<float> target)
    : BaseAttack(x, y, width, height, VELOCITY[level - 1], target,
                 DAMAGE[level - 1], BaseAttack::ARCHERY_ATTACK),
      Positionable(x, y) {}
