#include "Tower/BaseTower.hpp"
#include <chrono>
#include <cmath>
#include <memory>
#include <queue>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include "Enemy/BaseEnemy.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Map/EnemyPathTile.hpp"
#include "iostream"
#include "Map/Map.hpp"
#include "Tower/Towers/ArcheryTower.hpp"
#include "Tower/Towers/CatapultTower.hpp"
#include "Tower/Towers/ElectroTower.hpp"
#include "Tower/Towers/SlingshotTower.hpp"

// TODO: check the correct initialization for the sprite in BaseTower
BaseTower::BaseTower(std::shared_ptr<BaseTile> tile, unsigned range,
                     TowerType type, int price)

    : tile(tile),
      range(range),
      type(type),
      lvl(1),           // The starting level for each tower
      shoot_rate(1000)  // TODO: Elevate to subclasses
{
  // Initialize upgrades
  // TODO: Handle price decreasing : AFter thinking, handle it outside
  // Invariant: Current number of coins is already >= price
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

void BaseTower::upgrade() {
  if(get_level() < get_upgrades_count()) lvl++;
}

int BaseTower::get_upgrades_count() const {
  static std::unordered_map<BaseTower::TowerType, int> levels = {
    {BaseTower::ArcheryTower, ArcheryTower::LEVELS},
    {BaseTower::CatapultTower, CatapultTower::LEVELS},
    {BaseTower::ElectroTower, ElectroTower::LEVELS},
    {BaseTower::SlingshotTower, SlingshotTower::LEVELS},
};

  if (levels.find(get_type()) == levels.end())
    throw std::runtime_error("Unidentified tower type");
  return levels[get_type()];

}

int BaseTower::get_buy_price(BaseTower::TowerType type) {
  static std::unordered_map<BaseTower::TowerType, int> prices = {
      {BaseTower::ArcheryTower, ArcheryTower::PRICE},
      {BaseTower::CatapultTower, CatapultTower::PRICE},
      {BaseTower::ElectroTower, ElectroTower::PRICE},
      {BaseTower::SlingshotTower, SlingshotTower::PRICE},
  };

  if (prices.find(type) == prices.end())
    throw std::runtime_error("Unidentified tower type");
  return prices[type];
}

int BaseTower::get_upgrade_price() {
  return get_buy_price(type) * (get_level() + 1);
}

int BaseTower::get_sell_price() {
  int base_price = get_buy_price(type);

  int upgrades_price = 0;
  for (int level = 1; level < get_level(); level++) {
    upgrades_price += get_buy_price(type) * (level + 1);
  }

  // Sell for half the amount of coins spent on building the tower and its current upgrades
  return (base_price + upgrades_price)/2;
}

BaseTower::TowerType BaseTower::get_type() const { return type; }

Vector<float> BaseTower::get_position() const { return tile->get_position(); }

int BaseTower::get_level() const { return lvl; }

void BaseTower::reset_shoot_time() {
  last_shoot_time = std::chrono::steady_clock::now();
}

bool BaseTower::can_shoot() const {
  auto now = std::chrono::steady_clock::now();
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        now - last_shoot_time)
                        .count();
  return elapsed_ms >= shoot_rate;
}
