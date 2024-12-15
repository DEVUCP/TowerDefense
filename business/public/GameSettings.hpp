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
  GameSettings& get_instance();

  /*
   * @brief Return the size of the window
   */
  Vector<int> get_size();

  /*
   * @brief Return the size of a tile
   */
  Vector<int> get_tile_size();

  /*
   * @brief Return the number of rows and columns in the game
   */
  int get_rows();
  int get_columns();

private:
  GameSettings() = default;
};
