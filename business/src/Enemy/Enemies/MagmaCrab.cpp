#include "Enemy/Enemies/MagmaCrab.hpp"
#include "Enemy/BaseEnemy.hpp"

MagmaCrab::MagmaCrab(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, initial_health, velocity, kill_coins,
                EnemyType::LEAF_BUG) {}
