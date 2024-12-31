#include "Attack/Attacks/ElectroAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

ElectroAttack::ElectroAttack(int level, float x, float y, float width,
                             float height, Vector<float> target)
    : BaseAttack(x, y, width, height, VELOCITY[level], target, DAMAGE[level],
                 BaseAttack::ELECTRO_ATTACK),
      Positionable(x, y) {}
