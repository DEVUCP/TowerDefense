#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include "Attack/AttackManager.hpp"
#include "Attack/BaseAttack.hpp"
#include "Enemy/EnemyManager.hpp"
#include "Map/BuildableTile.hpp"
#include "Map/Map.hpp"
#include "Tower/TowerManager.hpp"
#include "Utils/Vector.hpp"
#include "WaveManager.hpp"

class Level {
public:
  static constexpr int frame_time_ms = 20;

public:
  enum GameState {
    PAUSED,
    ON,
    WON,
    LOST,
  };

public:
  Level(int lives, int coins, std::shared_ptr<Map> map,
        std::shared_ptr<WaveManager> wave_mng,
        std::shared_ptr<AttackManager> attack_mng,
        std::shared_ptr<TowerManager> tower_mng,
        std::shared_ptr<EnemyManager> enemy_mng, int level_num);

  /**
   * @brief modifier for lives
   *
   * @details modifies the player's lives based on the given amount.
   * If the resulted lives are less than zero, meaning that the player has
   * lost, calls end_game(false).
   *
   * @param amount The amount to subtract from the player's lives.
   */
  void decrease_lives(int amount);

  /**
   * @brief modifier for score
   *
   * @details Modifies the player's socre, and updates the xp in the Game
   * class as well.
   *
   * @param amount The +ve amount to be added the player's current score.
   */
  void increase_score(int amount);

  /**
   * @brief modifier for coins
   *
   * @details Modifying the player's coins in case of gaining/spending
   * coins.
   *
   * @param amount The amount to be add/subtract from the player's coins.
   * A +ve value represents winning more coins (by killing enemies).
   * A -ve represents purchasing a new tower/upgrade.
   *
   * @return bool, if true then the player gains coins or his purchase is
   * feasible. If false then the player doesn't have enough coins to
   * purchase that tower/upgrade.
   */
  bool update_coins(int amount);

  /**
   * @brief End Game
   *
   * @details assert the existence of a level. With ending the game, add
   * score to player's xp in Game class, and save it by `save_xp` in Game.
   *
   * @return <state, score> if bool is true, the player has won, and his
   * score is `score`. If false, he lost, and score is `score`
   */
  std::pair<bool, int> end_game();

  /**
   * @brief Check if the game is paused
   */
  bool is_paused() const;

  /**
   * @brief Check if the game has ended
   *
   * @details Will be helpful in the game loop to validate that the game
   * is not running anymore and has been LOST or WON.
   */
  bool has_ended() const;

  /**
   * @brief getter for the game state
   */
  GameState get_game_state() const;

  /**
   * @brief Run an iteration of the game loop
   *
   * @details in each iteration, the wave manager checks if the game is
   * done, the tower manager initializes new attacks, and the attack
   * amanger checks for attacks reaching target, and the enemy manager
   * moves all enemies
   */
  void run_iteration();

  /**
   * @brief Getters for managers
   */
  std::shared_ptr<TowerManager> get_tower_mng() const;
  std::shared_ptr<EnemyManager> get_enemy_mng() const;
  std::shared_ptr<WaveManager> get_wave_mng() const;
  std::shared_ptr<AttackManager> get_attack_mng() const;

  /**
   * @brief Getters for Map
   */
  std::shared_ptr<Map> get_map() const;
  /**
   * @brief Get the number of levels available
   * LevelReader::get_instance().levels_count();
   */
  static int get_level_count();

  /**
   * @brief Build a tower
   */
  std::shared_ptr<BaseTower> build_tower(BaseTower::TowerType,
                                         std::shared_ptr<BuildableTile> tile);

  /**
   * @brief Upgrade a tower
   */
  std::shared_ptr<BaseTower> upgrade_tower(std::shared_ptr<BaseTower> twr);

  /**
   * @brief Upgrade a tower
   */
  void sell_tower(std::shared_ptr<BaseTower> twr);

  /**
   * @brief Getters for game info
   */
  int get_lives() const;
  int get_score() const;
  int get_coins() const;

  /**
   * @brief Getters for the current level number
   */
  int get_level_num() const;

  /**
   * @brief Initiate an attack
   */
  void attack(std::shared_ptr<BaseTower> tower, float x, float y, float width,
              float height, Vector<float> target);

  /**
   * @brief Set Callbacks
   */
  void set_on_attack_created(std::function<void(std::shared_ptr<BaseAttack>)>);
  void set_on_enemy_created(std::function<void(std::shared_ptr<BaseEnemy>)>);
  void set_on_attack_hit(std::function<void(std::shared_ptr<BaseAttack>)>);
  void set_on_enemy_death(std::function<void(std::shared_ptr<BaseEnemy>)>);
  void set_on_enemy_out_of_bound(
      std::function<void(std::shared_ptr<BaseEnemy>)>);
  void set_on_attack_out_of_bound(
      std::function<void(std::shared_ptr<BaseAttack>)>);

  /**
   * @brief Run Callbacks
   */
  void on_attack_created(std::shared_ptr<BaseAttack>);
  void on_enemy_created(std::shared_ptr<BaseEnemy>);
  void on_attack_hit(std::shared_ptr<BaseAttack>);
  void on_enemy_death(std::shared_ptr<BaseEnemy>);
  void on_enemy_out_of_bound(std::shared_ptr<BaseEnemy>);
  void on_attack_out_of_bound(std::shared_ptr<BaseAttack>);

private:
  /**
   * @brief Initialize the default callbacks
   */
  void init_default_callbacks();

private:
  int lives;
  int score;
  int coins;
  std::shared_ptr<Map> map;
  std::shared_ptr<WaveManager> wave_mng;
  std::shared_ptr<EnemyManager> enemy_mng;
  std::shared_ptr<TowerManager> tower_mng;
  std::shared_ptr<AttackManager> attack_mng;
  GameState state;
  int level_num;

  // Callbacks
  std::vector<std::function<void(std::shared_ptr<BaseEnemy>)>>
      on_enemy_created_callbacks;
  std::vector<std::function<void(std::shared_ptr<BaseAttack>)>>
      on_attack_created_callbacks;
  std::vector<std::function<void(std::shared_ptr<BaseAttack>)>>
      on_attack_hit_callbacks;
  std::vector<std::function<void(std::shared_ptr<BaseAttack>)>>
      on_attack_out_of_bound_callbacks;
  std::vector<std::function<void(std::shared_ptr<BaseEnemy>)>>
      on_enemy_death_callbacks;
  std::vector<std::function<void(std::shared_ptr<BaseEnemy>)>>
      on_enemy_out_of_bound_callbacks;

  // Timer Info
  std::chrono::steady_clock::time_point last_run_time;  // Track last run time
};
