#include "Enemy/Enemies/LeafBug.hpp"
#include "Enemy/BaseEnemy.hpp"

LeafBug::LeafBug(float x, float y, float width, float height, Vector<float> dest)
    : BaseEnemy(x, y, width, height, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::LEAF_BUG) {}

void LeafBug::on_reach() {}
void LeafBug::on_out_of_board() {}
void LeafBug::on_killed() {}
