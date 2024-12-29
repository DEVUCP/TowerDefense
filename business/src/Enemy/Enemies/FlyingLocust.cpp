#include "Enemy/Enemies/FlyingLocust.hpp"

FlyingLocust::FlyingLocust(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::CLAMP_BEETLE),
      Positionable(x, y) {}

void FlyingLocust::on_killed() {}
