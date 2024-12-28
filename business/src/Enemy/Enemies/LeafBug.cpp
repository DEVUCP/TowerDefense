#include "Enemy/Enemies/LeafBug.hpp"
#include "Enemy/BaseEnemy.hpp"

LeafBug::LeafBug(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::LEAF_BUG),
      Positionable(x, y) {}

void LeafBug::on_killed() {}
