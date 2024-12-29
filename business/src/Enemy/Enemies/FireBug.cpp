#include "Enemy/Enemies/FireBug.hpp"

FireBug::FireBug(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::CLAMP_BEETLE),
      Positionable(x, y) {}

void FireBug::on_killed() {}
