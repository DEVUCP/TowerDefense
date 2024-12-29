#include "Enemy/Enemies/FireWasp.hpp"

FireWasp::FireWasp(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::CLAMP_BEETLE),
      Positionable(x, y) {}

void FireWasp::on_reach() {}
void FireWasp::on_out_of_board() {}
void FireWasp::on_killed() {}
