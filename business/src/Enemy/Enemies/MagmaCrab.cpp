#include "Enemy/Enemies/MagmaCrab.hpp"
#include "Enemy/BaseEnemy.hpp"

MagmaCrab::MagmaCrab(float x, float y, float width, float height, Vector<float> dest)
    : BaseEnemy(x, y, width, height, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::MAGMA_CRAB) {}
void MagmaCrab::on_reach() {}
void MagmaCrab::on_out_of_board() {}
void MagmaCrab::on_killed() {}
