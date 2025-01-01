#include "Enemy/BaseEnemy.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Map/EnemyPathTile.hpp"
#include "Utils/Collidable.hpp"
#include "Utils/Moveable.hpp"
#include "Utils/Positionable.hpp"

BaseEnemy::BaseEnemy(float x, float y, Vector<float> dest, int initial_health,
                     float velocity, int kill_coins, EnemyType type)

    : Positionable(x, y),
      Moveable(x, y, velocity, dest),
      Collidable(x - GameSettings::get_instance().get_enemy_width() / 2.f,
                 y - GameSettings::get_instance().get_enemy_height() / 2.f,
                 GameSettings::get_instance().get_enemy_width(),
                 GameSettings::get_instance().get_enemy_height()),
      kill_coins{kill_coins},
      type{type},
      health{initial_health},
      initial_health{health},
      state(BaseEnemy::ENTERING) {
  dest_tile =
      Game::get_instance().get_level()->get_map()->get_first_enemy_tile();
}

void BaseEnemy::handle_next_tile_redirection(std::shared_ptr<Map> map) {
  std::set<std::shared_ptr<BaseTile>> nearby =
      filter_tiles(get_nearby_tiles(map));
  // std::cout << nearby.size() << std::endl;
  update_current_tile(nearby);
}

void BaseEnemy::update_current_tile(
    std::set<std::shared_ptr<BaseTile>> nearby) {
  // Compute difference to find tiles to remove
  std::set<std::shared_ptr<BaseTile>> to_remove;
  std::set_difference(current_tiles.begin(), current_tiles.end(),
                      nearby.begin(), nearby.end(),
                      std::inserter(to_remove, to_remove.end()));

  // Remove outdated tiles
  for (auto& tile : to_remove) {
    auto converted = std::dynamic_pointer_cast<EnemyPathTile>(tile);
    assert(!!converted);
    converted->remove_enemy(shared_from_this());
    current_tiles.erase(tile);
  }

  // Add new tiles
  for (auto& tile : nearby) {
    // Only insert if needed
    if (current_tiles.find(tile) == current_tiles.end()) {
      auto converted = std::dynamic_pointer_cast<EnemyPathTile>(tile);
      assert(!!converted);
      converted->register_enemy(shared_from_this());
      current_tiles.insert(tile);
    }
  }
}

std::set<std::shared_ptr<BaseTile>> BaseEnemy::filter_tiles(
    std::set<std::shared_ptr<BaseTile>>&& nearby) {
  for (auto it = nearby.begin(); it != nearby.end();) {
    if ((*it)->get_type() != BaseTile::EnemyPath) {
      it = nearby.erase(it);
    } else {
      ++it;
    }
  }
  return nearby;
}

std::set<std::shared_ptr<BaseTile>> BaseEnemy::get_nearby_tiles(
    std::shared_ptr<Map> map) {
  auto nearby_tiles = std::set<std::shared_ptr<BaseTile>>();
  std::vector<Vector<float>> points;

  // Push the four corners of the enemy
  points.push_back(tl());
  points.push_back(tr());
  points.push_back(bl());
  points.push_back(br());

  // Add the points tiles
  for (auto p : points) {
    auto tile = map->map_coords_to_tile(p.x, p.y);
    // if (tile != nullptr)
    //   std::cout << "positions: " << p.x << " " << p.y
    //             << " and tile indices are " << tile->get_position().x / 120
    //             << " " << tile->get_position().y / 120 << std::endl;
    if (tile != nullptr) nearby_tiles.insert(tile);
  }
  return nearby_tiles;
}

void BaseEnemy::on_reach() {
  if (dest_tile ==
      Game::get_instance().get_level()->get_map()->get_last_enemy_tile())
    return;
  dest_tile++;
  update_dest((*dest_tile)->get_center());
  // TODO: Handle we are on last tile
}
const float BaseEnemy::get_health() const { return health; }

const float BaseEnemy::get_initial_health() const { return initial_health; }

BaseEnemy::EnemyState BaseEnemy::get_state() const { return state; }

void BaseEnemy::invoke_damage(float amount) {
  health -= amount;
  if (health <= 0) {
    state = DEAD;
    for (auto& tile : current_tiles) {
      auto converted = std::static_pointer_cast<EnemyPathTile>(tile);
      converted->remove_enemy(shared_from_this());
    }
    on_killed();
  }
}

BaseEnemy::EnemyType BaseEnemy::get_type() const { return type; }

void BaseEnemy::on_out_of_board() {
  if (state == ON_BOARD) state = OUT_BOUND;
}

void BaseEnemy::on_move() {
  auto map = Game::get_instance().get_level()->get_map();
  handle_next_tile_redirection(map);
  check_state();
}

void BaseEnemy::check_state() {
  auto [width, height] = GameSettings::get_instance().get_size();
  auto pos = get_position();
  if (state == ENTERING) {
    if (pos.x > 0 && pos.x < width && pos.y > 0 && pos.y < height)
      state = ON_BOARD;
  }
}

int BaseEnemy::get_kill_coins() const { return kill_coins; }
