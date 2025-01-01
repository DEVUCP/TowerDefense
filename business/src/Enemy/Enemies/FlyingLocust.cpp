#include "Enemy/Enemies/FlyingLocust.hpp"

FlyingLocust::FlyingLocust(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::FLYING_LOCUST),
      Positionable(x, y) {}

void FlyingLocust::on_killed() {}
