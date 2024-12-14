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

private:
  std::vector<std::vector<std::shared_ptr<BaseTile>>> grid;
  std::list<std::shared_ptr<EnemyPathTile>> enemyPath;
};
