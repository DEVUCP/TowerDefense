#include "Enemy/Enemies/ClampBeetle.hpp"

ClampBeetle::ClampBeetle(float x, float y, float width, float height, Vector<float> dest)
    : BaseEnemy(x, y, width, height, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::CLAMP_BEETLE) {}

void ClampBeetle::on_reach() {}
void ClampBeetle::on_out_of_board() {}
void ClampBeetle::on_killed() {}
