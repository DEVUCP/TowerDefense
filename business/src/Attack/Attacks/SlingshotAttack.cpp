#include "Attack/Attacks/SlingshotAttack.hpp"
#include "Attack/BaseAttack.hpp"
#include "Utils/Positionable.hpp"

SlingshotAttack::SlingshotAttack(int level, float x, float y, float width,
                                 float height, Vector<float> target)
    : BaseAttack(x, y, width, height, VELOCITY[level], target, DAMAGE[level],
                 BaseAttack::SLINGSHOT_ATTACK),
      Positionable(x, y) {}
