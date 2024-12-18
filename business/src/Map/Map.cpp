#include "Map/Map.hpp"

Map::Map(std::vector<std::vector<std::shared_ptr<BaseTile>>>&& grid,
         std::list<std::shared_ptr<EnemyPathTile>>&& path) {
  this->grid = std::move(grid);
  enemy_path = std::move(path);
}

std::shared_ptr<BaseTile> Map::map_coords_to_tile(float x, float y) const {
  int i = x / TILE_LENGTH, j = y / TILE_LENGTH;
  return grid[i][j];
}
std::shared_ptr<BaseTile> tile_coords_to_tile(int i, int j) const{
  return grid[i][j];
}