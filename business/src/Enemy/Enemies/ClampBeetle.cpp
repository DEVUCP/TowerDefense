#include "Enemy/Enemies/ClampBeetle.hpp"

ClampBeetle::ClampBeetle(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, initial_health, velocity, kill_coins,
                EnemyType::CLAMP_BEETLE) {}
