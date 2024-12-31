#include "Map/Map.hpp"
#include <iostream>
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
  auto pos = (*enemy_path.begin())->get_center();
  auto offset = GameSettings::get_instance().get_tile_size();
  auto [i, j] = map_coords_to_indices(pos.x, pos.y);
  if (i == 0)
    pos.y -= offset;
  else if (i == 12)
    pos.y += offset;
  else if (j == 0)
    pos.x -= offset;
  else if (j == 12)
    pos.x += offset;
  return pos;
}

const Vector<float> Map::get_initial_enemy_destination() const {
  assert(!enemy_path.empty());
  return (*enemy_path.begin())->get_center();
}

std::pair<int, int> Map::map_coords_to_indices(float x, float y) const {
  auto len = GameSettings::get_instance().get_tile_size();
  int j = x / len, i = y / len;
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

bool Map::is_on_map(Vector<float> pos) const {
  auto [width, height] = GameSettings::get_instance().get_size();
  return pos.x > 0 && pos.x < width && pos.y > 0 && pos.y > height;
}
