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
  Vector<unsigned> get_size() const;

  /*
   * @brief Return the size of a tile
   */
  unsigned get_tile_size() const;

  /*
   * @brief Return the number of rows and columns in the game
   */
  unsigned get_rows() const;
  unsigned get_columns() const;

  /*
   * @brief Return the number of rows for the sidebar
   */
  unsigned get_sidebar_row_count() const;

private:
  GameSettings() = default;
};