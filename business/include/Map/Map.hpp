#pragma once

#include <list>
#include <memory>
#include <utility>
#include <vector>
#include "Map/BaseTile.hpp"

class EnemyPathTile;

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

  /**
   * @brief Map Game Coordinates to a tile indices
   */
  std::pair<int, int> map_coords_to_indices(float x, float y) const;

  /**
   * @brief Return the tile at given indices
   */
  std::shared_ptr<BaseTile> get_tile(int i, int j) const;

  /**
   * @brief Get First Enemy Position
   */
  const Vector<float> get_initial_enemy_position() const;

  /**
   * @brief Return the first destination for the enemies spawned
   *
   * @details The first enemy position is the same as the center of the first
   * enemy path tile
   */
  const Vector<float> get_initial_enemy_destination() const;

private:
  std::vector<std::vector<std::shared_ptr<BaseTile>>> grid;
  std::list<std::shared_ptr<EnemyPathTile>> enemy_path;
};
