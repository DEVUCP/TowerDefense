#include "Enemy/Enemies/MagmaCrab.hpp"
#include "Enemy/BaseEnemy.hpp"

MagmaCrab::MagmaCrab(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::MAGMA_CRAB),
      Positionable(x, y) {}
void MagmaCrab::on_reach() {}
void MagmaCrab::on_out_of_board() {}
void MagmaCrab::on_killed() {}
