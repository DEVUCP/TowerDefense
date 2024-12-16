#include "Map/Map.hpp"

Map::Map(std::vector<std::vector<std::shared_ptr<BaseTile>>>&& grid,
         std::list<std::shared_ptr<EnemyPathTile>>&& path) {
  this->grid = std::move(grid);
  enemy_path = std::move(path);
}

std::shared_ptr<BaseTile> Map::map_coords_to_tile(float x, float y) const {
  int i = x / 60, j = y / 60;
  return grid[i][j];
}
