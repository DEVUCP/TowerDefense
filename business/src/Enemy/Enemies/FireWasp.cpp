#include "Enemy/Enemies/FireWasp.hpp"

FireWasp::FireWasp(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::FIRE_WASP),
      Positionable(x, y) {}

void FireWasp::on_killed() {}
