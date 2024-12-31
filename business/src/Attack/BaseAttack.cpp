#include "Attack/BaseAttack.hpp"
#include <iostream>
#include <memory>
#include "Enemy/BaseEnemy.hpp"
#include "Game.hpp"
#include "Map/EnemyPathTile.hpp"
#include "Utils/Positionable.hpp"

BaseAttack::BaseAttack(float x, float y, float width, float height,
                       float velocity, Vector<float> target, int damage,
                       AttackType type)
    : Moveable(x, y, velocity, target),
      Collidable(x, y, width, height),
      Positionable(x, y),
      damage(damage),
      type{type},
      state(MOVING) {
  // std::cout << "Attack target: " << target.x << " " << target.y << std::endl;
}

BaseAttack::AttackState BaseAttack::get_state() const { return state; }

std::shared_ptr<BaseEnemy> BaseAttack::check_collisions(
    std::shared_ptr<Map> map) {
  // get nearby tiles
  // filter tiles
  auto nearby = filter_tiles(get_nearby_tiles(map));

  // std::cout << "Tiles Indices: " << std::endl;
  // for (auto& tile : nearby) {
  //   std::cout << tile->get_position().y / 120 << " "
  //             << tile->get_position().x / 120 << std::endl;
  // }
  // get enemies in current tile(s)
  std::set<std::shared_ptr<BaseEnemy>> enemies;
  for (auto& tile : nearby) {
    auto converted = std::static_pointer_cast<EnemyPathTile>(tile);
    auto tile_enemies = converted->get_enemies();
    for (auto& enemy : tile_enemies) enemies.insert(enemy);
  }

  if (enemies.empty()) return nullptr;

  // filter non colliding enemies
  for (auto itr = enemies.begin(); itr != enemies.end();) {
    if (hit(*itr))
      itr++;
    else
      itr = enemies.erase(itr);
  }

  if (!enemies.size()) return nullptr;
  // std::cout << "Checking against " << enemies.size() << " enemies" <<
  // std::endl;

  // find nearest enemy
  auto enemy_to_affect = *enemies.begin();
  for (auto& enemy : enemies) {
    if (get_position().get_distance_to(enemy->get_position()) <
        get_position().get_distance_to(enemy_to_affect->get_position()))
      enemy_to_affect = enemy;
  }
  // std::cout << "will apply damage" << std::endl;

  return enemy_to_affect;
}

std::set<std::shared_ptr<BaseTile>> BaseAttack::filter_tiles(
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

std::set<std::shared_ptr<BaseTile>> BaseAttack::get_nearby_tiles(
    std::shared_ptr<Map> map) {
  static std::vector directions = {-1, 0, 1};

  auto nearby_tiles = std::set<std::shared_ptr<BaseTile>>();
  auto list = {tl(), tr(), bl(), br()};
  for (auto& v : list) {
    for (auto x : directions)
      for (auto y : directions) {
        int dx = v.x + x, dy = v.y + y;
        auto tile = map->map_coords_to_tile(dx, dy);
        if (tile == nullptr) continue;
        nearby_tiles.insert(tile);
      }
  }
  return nearby_tiles;
}

bool BaseAttack::hit(std::shared_ptr<BaseEnemy> enemy) {
  return collide_with(static_cast<const Collidable&>(*enemy));
}

void BaseAttack::on_hit() {}
void BaseAttack::on_move() {
  std::cout << "Attack: " << get_position().x << " " << get_position().y
            << std::endl;
  auto map = Game::get_instance().get_level()->get_map();
  auto enemy = check_collisions(map);
  if (enemy == nullptr) return;
  enemy->invoke_damage(damage);
}

void BaseAttack::on_reach() {
  // to_be_removed = true;
}
void BaseAttack::on_out_of_board() { state = OUT; }

BaseAttack::AttackType BaseAttack::get_type() { return type; }
