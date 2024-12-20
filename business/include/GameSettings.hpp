#pragma once

#include "Utils/Vector.hpp"

class GameSettings {
public:
  // remove copying
  GameSettings(const GameSettings&) = delete;
  GameSettings& operator=(const GameSettings&) = delete;

  /*
   * @brief Get the one instance
   */
  static GameSettings& get_instance();

  /*
   * @brief Return the size of the window
   */
  Vector<unsigned> get_size();

  /*
   * @brief Return the size of a tile
   */
  unsigned get_tile_size();

  /*
   * @brief Return the number of rows and columns in the game
   */
  unsigned get_rows();
  unsigned get_columns();

private:
  GameSettings() = default;
};
