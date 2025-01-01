#include "Enemy/Enemies/VoidButterfly.hpp"

VoidButterfly::VoidButterfly(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::VOID_BUTTERFLY),
      Positionable(x, y) {}

void VoidButterfly::on_killed() {}
