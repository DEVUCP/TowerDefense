#include "Attack/BaseAttack.hpp"
#include <algorithm>
#include "Map/EnemyPathTile.hpp"
#include "Utils/Positionable.hpp"

BaseAttack::BaseAttack(float x, float y, float width, float height,
                       float velocity, Vector<float> target,
                       const std::string& sprite, int damage)
    : Moveable(x, y, velocity, target),
      Collidable(x, y, width, height),
      Positionable(x, y),
      damage(damage) {}

bool BaseAttack::is_to_be_removed() { return to_be_removed; }

void BaseAttack::check_collisions(std::shared_ptr<Map> map) {
  // get nearby tiles
  // filter tiles
  std::vector<std::shared_ptr<BaseTile>> nearby =
      filter_tiles(get_nearby_tiles(map));

  // update current tile
  current_tile = nearby;

  // get enemies in current tile(s)
  std::vector<std::shared_ptr<BaseEnemy>> enemies;
  for (int i = 0; i < nearby.size(); i++) {
    auto enemy_path_tile = static_cast<EnemyPathTile*>(nearby[i].get());
    enemies.insert(enemies.end(), enemy_path_tile->get_enemies().begin(),
                   enemy_path_tile->get_enemies().end());
  }

  if (enemies.empty()) return;

  // filter non colliding enemies
  for (int i = 0; i < enemies.size(); i++) {
    if (!hit(enemies[i])) enemies.erase(enemies.begin() + i);
  }

  // find nearest enemy
  float shortest_distance_index = 0;
  for (int i = 0; i < enemies.size(); i++) {
    if (get_position().get_distance_to(enemies[i]->get_position()) <
        get_position().get_distance_to(
            enemies[shortest_distance_index]->get_position()))
      shortest_distance_index = i;
  }

  // apply damage to nearest (im not sure with the architecture, omar)
}

std::vector<std::shared_ptr<BaseTile>> BaseAttack::filter_tiles(
    std::vector<std::shared_ptr<BaseTile>> nearby) {
  auto it = std::unique(nearby.begin(), nearby.end());
  nearby.erase(it, nearby.end());

  for (int i = 0; i < nearby.size(); i++) {
    if (nearby[i]->get_type() != BaseTile::EnemyPath)
      nearby.erase(nearby.begin() + i);
  }
  return nearby;
}

std::vector<std::shared_ptr<BaseTile>> BaseAttack::get_nearby_tiles(
    std::shared_ptr<Map> map) {
  std::vector<std::shared_ptr<BaseTile>> nearby_tiles =
      std::vector<std::shared_ptr<BaseTile>>();
  nearby_tiles.push_back(map->map_coords_to_tile(tl().x, tl().y));
  nearby_tiles.push_back(map->map_coords_to_tile(tr().x, tr().y));
  nearby_tiles.push_back(map->map_coords_to_tile(bl().x, bl().y));
  nearby_tiles.push_back(map->map_coords_to_tile(br().x, br().y));
  return nearby_tiles;
}

bool BaseAttack::hit(std::shared_ptr<BaseEnemy> enemy) {
  return collide_with(static_cast<const Collidable&>(*enemy));
}

void BaseAttack::on_hit() {}
void BaseAttack::on_move() {}

void BaseAttack::on_reach() { to_be_removed = true; }
void BaseAttack::on_out_of_board() { to_be_removed = true; }
