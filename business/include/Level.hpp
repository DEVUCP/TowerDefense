#pragma once

#include <memory>
#include "Attack/AttackManager.hpp"
#include "Enemy/EnemyManager.hpp"
#include "Map/Map.hpp"
#include "Tower/TowerManager.hpp"
#include "WaveManager.hpp"

class Level {
public:
  Level(int lives, int score, int coins, std::shared_ptr<Map> map);

  /**
   * @brief modifiers for lives, score, and coins
   */
  void decrease_lives(int amount);  // < check if not negative
  void increase_score(int amount);  // Update game xp as well
  void increase_coins(int amount);  // < check if not negative

  /**
   * @brief Start the game by initializing a level by `init_level`
   *
   * @details assert that there was no level
   */

  void start_game();

  /**
   * @brief End Game
   *
   * @details assert the existence of a level. With ending the game, add score
   * to player's xp in Game class, and save it by `save_xp` in Game.
   */
  void end_game();

  /**
   * @brief Check if the game is paused
   */
  bool is_paused() const;

  /**
   * @brief Run an iteration of the game loop
   *
   * @details in each iteration, the wave manager checks if the game is done,
   * the tower manager initializes new attacks, and the attack amanger checks
   * for attacks reaching target, and the enemy manager moves all enemies
   */
  void run_iteration();

private:
  /**
   * @brief Initialize a level by using
   * LevelReader::get_instance().build_level(level_num);
   */
  void init_level(int level_num);

private:
  int lives;
  int score;
  int coins;
  std::shared_ptr<Map> map;
  WaveManager wave_mng;
  EnemyManager enemy_mng;
  TowerManager tower_mng;
  AttackManager attack_mng;
  bool pause;  // < indicate if the game is paused by presentation layer
};
