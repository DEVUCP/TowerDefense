#include "Enemy/Enemies/ClampBeetle.hpp"

ClampBeetle::ClampBeetle(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::CLAMP_BEETLE),
      Positionable(x, y) {}

void ClampBeetle::on_killed() {}
