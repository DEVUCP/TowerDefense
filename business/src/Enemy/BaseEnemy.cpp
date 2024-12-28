#include "Enemy/BaseEnemy.hpp"
#include <algorithm>
#include "Game.hpp"
#include "Utils/Moveable.hpp"

BaseEnemy::BaseEnemy(float x, float y, float width, float height,
                     Vector<float> dest, int initial_health, float velocity,
                     int kill_coins, EnemyType type)
    : Moveable(x, y, velocity, dest),
      kill_coins{kill_coins},
      type{type},
      health{initial_health},
      initial_health{health},
      Collidable(x, y, width, height),
      to_be_removed(false) {}

void BaseEnemy::handle_next_tile_redirection(std::shared_ptr<Map> map) {}

void BaseEnemy::update_current_tile(
    std::vector<std::shared_ptr<BaseTile>> nearby) {
  if (current_tile.empty() && nearby.size() == 1) {
    current_tile.push_back(nearby[0]);
    return;
  }

  if (nearby.size() == 2) {
    if (current_tile.front() == nearby[0] && current_tile[1] == nearby[1])
      return;
    if (current_tile.front() == nearby[0] && current_tile[1] != nearby[1]) {
      current_tile.push_back(nearby[1]);
      return;
    }
    if (current_tile.front() == nearby[1] && current_tile[1] == nearby[0])
      return;
    if (current_tile.front() == nearby[1] && current_tile[1] != nearby[0]) {
      current_tile.push_back(nearby[0]);
      return;
    }
    current_tile.erase(current_tile.begin());
    current_tile.push_back(nearby[0]);
    current_tile.push_back(nearby[1]);
    return;
  }
}

std::vector<std::shared_ptr<BaseTile>> BaseEnemy::filter_tiles(
    std::vector<std::shared_ptr<BaseTile>> nearby) {
  auto it = std::unique(nearby.begin(), nearby.end());
  nearby.erase(it, nearby.end());

  for (int i = 0; i < nearby.size(); i++) {
    if (nearby[i]->get_type() != BaseTile::EnemyPath)
      nearby.erase(nearby.begin() + i);
  }
  return nearby;
}

std::vector<std::shared_ptr<BaseTile>> BaseEnemy::get_nearby_tiles(
    std::shared_ptr<Map> map) {
  // return the tiles of all 4 points of collidable
  std::vector<std::shared_ptr<BaseTile>> nearby_tiles =
      std::vector<std::shared_ptr<BaseTile>>();
  nearby_tiles.push_back(map->map_coords_to_tile(tl().x, tl().y));
  nearby_tiles.push_back(map->map_coords_to_tile(tr().x, tr().y));
  nearby_tiles.push_back(map->map_coords_to_tile(bl().x, bl().y));
  nearby_tiles.push_back(map->map_coords_to_tile(br().x, br().y));
  return nearby_tiles;
}

void BaseEnemy::on_reach() {
  handle_next_tile_redirection(Game::get_instance().get_level()->get_map());
}
const float BaseEnemy::get_health() const { return health; }

const float BaseEnemy::get_initial_health() const { return initial_health; }

const bool BaseEnemy::is_to_be_removed() const { return to_be_removed; }

void BaseEnemy::invoke_damage(float amount) {
  health -= amount;
  if (health <= 0) on_killed();
}

BaseEnemy::EnemyType BaseEnemy::get_type() const { return type; }

void BaseEnemy::on_out_of_board() {}
