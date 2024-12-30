#include "Attack/Attacks/ArcheryAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

ArcheryAttack::ArcheryAttack(float x, float y, float width, float height,
                             Vector<float> target)
    : BaseAttack(x, y, width, height, VELOCITY, target, DAMAGE,
                 BaseAttack::ARCHERY_ATTACK),
      Positionable(x, y) {}
