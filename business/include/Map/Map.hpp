#pragma once

#include <list>
#include <memory>
#include <vector>
#include "Map/BaseTile.hpp"
#include "Map/EnemyPathTile.hpp"

/**
 * @class Map
 * @brief Represents the map of a level
 *
 * Initiliazed as part of the level
 */
class Map {
public:
  /**
   * @brief Constructor with rvalues
   */
  Map(std::vector<std::vector<std::shared_ptr<BaseTile>>>&&,
      std::list<std::shared_ptr<EnemyPathTile>>&& path);

  /**
   * @brief Map coordinates to a tile
   *
   * Given a coordinates in the game, return the tile on which these coordinates
   * where
   *
   * @return Return the tile if it's in the game or nullptr instead
   */
  std::shared_ptr<BaseTile> map_coords_to_tile(float x, float y) const;
  std::shared_ptr<BaseTile> tile_coords_to_tile(int i, int j) const;

private:
  std::vector<std::vector<std::shared_ptr<BaseTile>>> grid;
  std::list<std::shared_ptr<EnemyPathTile>> enemy_path;
};
