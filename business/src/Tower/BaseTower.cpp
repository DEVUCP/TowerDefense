#include "Tower/BaseTower.hpp"
#include <cmath>
#include <memory>
#include <queue>
#include <set>
#include "Enemy/BaseEnemy.hpp"
#include "Map/EnemyPathTile.hpp"
#include "Map/Map.hpp"

// TODO: check the correct initialization for the sprite in BaseTower
BaseTower::BaseTower(std::shared_ptr<BaseTile> tile, unsigned range,
                     unsigned attack_speed, unsigned attack_damage,
                     TowerType type)

    : tile(tile),
      range(range),
      attack_speed(attack_speed),
      damage(attack_damage),
      type(type),
      lvl(1)  // The starting level for each tower
{
  // Initialize upgrades
}

void BaseTower::init_attack(std::shared_ptr<BaseEnemy> enemy) {
  // std::cout << "Attacking enemy at position: " << enemy->get_position()
  //           << std::endl;
  // enemy->invoke_damage(damage);
  // TODO: Implement attack logic here
}

bool BaseTower::in_range(std::shared_ptr<Map> map) {
  if (!map) return false;

  // Starting position of the tower
  auto start_tile = tile;
  auto pos = tile->get_position();
  if (!start_tile) return false;

  // BFS setup: Pair contains the tile and current depth
  std::queue<std::pair<std::shared_ptr<BaseTile>, int>> to_visit;
  std::set<std::shared_ptr<BaseTile>> visited;

  to_visit.push({start_tile, 0});
  visited.insert(start_tile);

  while (!to_visit.empty()) {
    auto [current_tile, depth] = to_visit.front();
    to_visit.pop();

    // Stop if the depth exceeds the range
    if (depth > static_cast<int>(range)) continue;

    // Check if the tile is an EnemyPathTile
    if (current_tile->get_type() == BaseTile::EnemyPath) {
      auto enemy_path_tile =
          std::dynamic_pointer_cast<EnemyPathTile>(current_tile);
      auto enemies = enemy_path_tile->get_enemies();
      if (!enemies.empty()) {
        // Attack the first enemy found
        init_attack(enemies.front());
        return true;
      }
    }

    // Add unvisited neighbors to the BFS queue
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (dx == 0 && dy == 0) continue;  // Skip the current tile

        int neighbor_x = pos.x + dx;
        int neighbor_y = pos.y + dy;

        auto neighbor_tile = map->get_tile(neighbor_x, neighbor_y);
        if (neighbor_tile && visited.find(neighbor_tile) == visited.end()) {
          to_visit.push({neighbor_tile, depth + 1});
          visited.insert(neighbor_tile);
        }
      }
    }
  }

  return false;  // No enemies found within range
}

void BaseTower::upgrade(int upgrade_index) {}

// TODO: change base_price
int BaseTower::get_sell_price() {
  // int base_price = 200;  // Example base price
  // int upgrade_value =
  //     upgrades ? upgrades->get_cost() / 2 : 0;  // Half of upgrade cost
  // return base_price + upgrade_value;
  return 0;
}

BaseTower::TowerType BaseTower::get_type() const { return type; }

Vector<float> BaseTower::get_position() const { return tile->get_position(); }
