#include "Enemy/BaseEnemy.hpp"
#include "Utils/Moveable.hpp"

BaseEnemy::BaseEnemy(float x, float y, float velocity,
                     std::shared_ptr<BaseTile> current_tile, Vector<float> dest,
                     const std::string& sprite, int kill_coins)
    : Drawable(sprite, Vector<float>(0, 0)), Moveable(x, y, velocity, dest) {
  this->current_tile = current_tile;
  this->kill_coins = kill_coins;
}

void BaseEnemy::handle_next_tile_redirection(std::shared_ptr<Map> map) {}

const float BaseEnemy::get_health() const { return health; }

const std::shared_ptr<BaseTile> BaseEnemy::get_position() const { return current_tile; }

const float BaseEnemy::get_initial_health() const { return initial_health; }

const bool BaseEnemy::is_to_be_removed() const { return to_be_removed; }

void BaseEnemy::invoke_damage(float amount) {
  health -= amount;
  if (health <= 0) on_killed();
}

BaseEnemy::EnemyType BaseEnemy::get_type() const { return type; }
