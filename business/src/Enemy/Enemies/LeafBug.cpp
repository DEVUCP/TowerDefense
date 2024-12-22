#include "Enemy/Enemies/LeafBug.hpp"
#include "Enemy/BaseEnemy.hpp"

LeafBug::LeafBug(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, initial_health, velocity, kill_coins,
                EnemyType::LEAF_BUG) {}
