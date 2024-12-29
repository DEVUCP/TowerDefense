#include "Tower/BaseTower.hpp"
#include <cmath>
#include <memory>
#include <queue>
#include <set>
#include "Enemy/BaseEnemy.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Map/EnemyPathTile.hpp"
#include "Map/Map.hpp"
#include "Tower/Towers/ArcheryTower.hpp"
#include "Tower/Towers/IonPrism.hpp"

// TODO: check the correct initialization for the sprite in BaseTower
BaseTower::BaseTower(std::shared_ptr<BaseTile> tile, unsigned range,
                     TowerType type)

    : tile(tile),
      range(range),
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

std::vector<std::shared_ptr<BaseEnemy>> BaseTower::enemies_in_range() {
  auto map = Game::get_instance().get_level()->get_map();
  if (!map) return {};  // Return an empty vector if the map is not found

  // Starting position of the tower
  auto start_tile = tile;
  if (!start_tile)
    return {};  // Return an empty vector if the tile is not valid

  // BFS setup: Pair contains the tile and current depth
  std::queue<std::pair<std::shared_ptr<BaseTile>, int>> to_visit;
  std::set<std::shared_ptr<BaseTile>> visited;

  to_visit.push({start_tile, 0});
  visited.insert(start_tile);

  // Vector to hold all found enemies
  std::vector<std::pair<int, std::shared_ptr<BaseEnemy>>> enemies_in_range;

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
        // For each enemy on the current tile, store it with the distance
        // (depth)
        for (auto& enemy : enemies) {
          enemies_in_range.push_back({depth, enemy});
        }
      }
    }

    // Get the tile's position in the map (assuming tile is indexed by x and y)
    auto len = GameSettings::get_instance().get_tile_size();
    auto x = current_tile->get_position().y / len;
    auto y = current_tile->get_position().x / len;

    // Add unvisited neighbors to the BFS queue
    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (dx == 0 && dy == 0) continue;  // Skip the current tile

        int neighbor_x = x + dx;
        int neighbor_y = y + dy;
        auto neighbor_tile = map->get_tile(neighbor_x, neighbor_y);
        if (neighbor_tile && visited.find(neighbor_tile) == visited.end()) {
          to_visit.push({neighbor_tile, depth + 1});
          visited.insert(neighbor_tile);
        }
      }
    }
  }

  // Sort enemies by distance (closest first)
  std::sort(enemies_in_range.begin(), enemies_in_range.end(),
            [](const auto& a, const auto& b) {
              return a.first < b.first;  // Compare by distance (depth)
            });

  // Extract only the enemies (ignoring distance)
  std::vector<std::shared_ptr<BaseEnemy>> sorted_enemies;
  for (const auto& enemy_pair : enemies_in_range) {
    sorted_enemies.push_back(enemy_pair.second);
  }

  return sorted_enemies;
}

void BaseTower::upgrade(int upgrade_index) {}

int BaseTower::get_buy_price(BaseTower::TowerType type) {
  int price;

  switch (type) {
    case IonPrism:
      price = IonPrism::PRICE;
      break;
    case ArcheryTower:
      price = ArcheryTower::PRICE;
      break;
    default:
      price = 0;
  }

  return price;
}

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

int BaseTower::get_level() const { return lvl; }
