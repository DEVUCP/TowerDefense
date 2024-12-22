#include "Enemy/BaseEnemy.hpp"
#include "Utils/Moveable.hpp"

BaseEnemy::BaseEnemy(float x, float y, Vector<float> dest, int initial_health,
                     float velocity, int kill_coins, EnemyType type)
    : Moveable(x, y, velocity, dest),
      kill_coins{kill_coins},
      type{type},
      health{initial_health},
      initial_health{health},
      to_be_removed(false) {}

void BaseEnemy::handle_next_tile_redirection(std::shared_ptr<Map> map) {}

const float BaseEnemy::get_health() const { return health; }

const float BaseEnemy::get_initial_health() const { return initial_health; }

const bool BaseEnemy::is_to_be_removed() const { return to_be_removed; }

void BaseEnemy::invoke_damage(float amount) {
  health -= amount;
  if (health <= 0) on_killed();
}

BaseEnemy::EnemyType BaseEnemy::get_type() const { return type; }
