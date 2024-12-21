#include "Map/Map.hpp"
#include "GameSettings.hpp"

Map::Map(std::vector<std::vector<std::shared_ptr<BaseTile>>>&& grid,
         std::list<std::shared_ptr<EnemyPathTile>>&& path)
    : grid(grid), enemy_path(path) {}

std::shared_ptr<BaseTile> Map::map_coords_to_tile(float x, float y) const {
  auto len = GameSettings::get_instance().get_tile_size();
  int i = x / len, j = y / len;
  return get_tile(i, j);
}

std::shared_ptr<BaseTile> Map::get_tile(int i, int j) const {
  return grid[i][j];
}
