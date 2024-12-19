#pragma once

#include <memory>
#include "Level.hpp"

class Game {
public:
  // Delete copying
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  /**
   * @brief Get the one instance of the Game
   */
  static Game& get_instance();

  /**
   * @brief Get Level
   */

  std::shared_ptr<Level> get_level();

private:
  Game();  // < private constructor

private:
  std::shared_ptr<Level> lvl;  // < if null, the game hasn't started
};
