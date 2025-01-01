#include "Enemy/Enemies/Scorpion.hpp"

Scorpion::Scorpion(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::SCORPION),
      Positionable(x, y) {}

void Scorpion::on_killed() {}
