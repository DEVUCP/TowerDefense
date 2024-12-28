#include "Map/Map.hpp"
#include "GameSettings.hpp"
#include "Map/EnemyPathTile.hpp"

Map::Map(std::vector<std::vector<std::shared_ptr<BaseTile>>>&& grid,
         std::list<std::shared_ptr<EnemyPathTile>>&& path)
    : grid(grid), enemy_path(path) {}

std::shared_ptr<BaseTile> Map::map_coords_to_tile(float x, float y) const {
  auto [i, j] = map_coords_to_indices(x, y);
  return get_tile(i, j);
}

std::shared_ptr<BaseTile> Map::get_tile(int i, int j) const {
  if (!(i >= 0 && i < grid.size())) return nullptr;
  if (!(j >= 0 && j < grid[0].size())) return nullptr;
  return grid[i][j];
}

const Vector<float> Map::get_initial_enemy_position() const {
  // TODO:
  return {0, 0};
}

const Vector<float> Map::get_initial_enemy_destination() const {
  assert(!enemy_path.empty());
  return (*enemy_path.begin())->get_center();
}

std::pair<int, int> Map::map_coords_to_indices(float x, float y) const {
  auto len = GameSettings::get_instance().get_tile_size();
  int i = x / len, j = y / len;
  return {i, j};
}

Map::enemy_path_list::iterator Map::get_first_enemy_tile() {
  return enemy_path.begin();
}
Map::enemy_path_list::iterator Map::get_last_enemy_tile() {
  auto itr = enemy_path.end();
  --itr;
  return itr;
}
