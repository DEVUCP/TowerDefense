#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Utils/Drawable.hpp"
#include "Utils/Vector.hpp"

class BaseAttack;  // Declare class without any interface. To use the interface,
                   // include the header file in source file

/**
 * @class BaseTile
 * @brief Represent the base class for all tiles to inherit
 */
class BaseTile : public Drawable {
public:  // public types
  /**
   * @enum TileType
   * @brief Represents the type of a tile
   *
   * A type can be be
   * 1. Buildable: A tower can be built upon this tile
   * 2. NonBuildable: No tower can be built upon this tile. only for aesthetics
   * of the map
   * 3. EnemyPath: No tower can be built upon this tile. Only for the traversal
   * of the enemy
   */
  enum TileType {
    Buildable,
    NonBuildable,
    EnemyPath,
  };

public:
  /**
   * @brief Constructor
   */
  BaseTile(TileType type);

  /**
   * @brief return center coordinates
   *
   * @details use GameSettings::get_instance()
   */
  Vector<float> get_center() const;

private:
  TileType type;
  Vector<float> position;
};
