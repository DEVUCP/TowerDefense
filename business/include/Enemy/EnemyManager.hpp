#pragma once
#include <map>
#include <unordered_map>
#include <utility>
#include "BaseEnemy.hpp"
#include "Enemy/BaseEnemy.hpp"

class EnemyManager {
public:
  /**
   * @brief Assign a number of tickets to an enemy type
   */
  void assign_tickets(BaseEnemy::EnemyType, int);

  /*
   * @breif Given the tickets, generate a random enemy with the given
   * probabilites represented by tickets
   *
   * @details
   * This idea is inspired by a concept known as `lottery scheduling`. It's
   * based on each enemy having a number of tickets. The more tickets it has,
   * the more probabily it will be called
   *
   * Say we have the tickets and we are in 7th wave
   * ANT: 300 [1 - 300] - open from 1st wave
   * COCKROACH: 200 [301 - 500] - open from 3rd wave
   * BETTLE: 100 [501 - 600] - open from 5th wave
   *
   * We select a random number from 1 to 600 [total of tickets since all enemies
   * are available], We choose 503. We first traverse the list of tickets, we
   * have only 300 hundered, so this is not the target, we look for 503-300 in
   * the remaining of the list, and get 200 for cockroach, we don't have enough
   * tickets, so we search for 503-300-200 which is < then 100. so we generate a
   * bettle
   *
   * If we are in 3rd wave, total tickets are 500 only since we cannot generate
   * bettles
   */
  std::shared_ptr<BaseEnemy> generate_enemy(const int &starting_wave);

  /**
   * @brief Get the starting wave for a specific enemy type.
   *
   * @param type The enemy type whose starting wave is to be retrieved.
   * @return The wave number in which the enemy becomes available.
   */
  int get_starting_wave(BaseEnemy::EnemyType type) const;

  /**
   * @brief Set the starting wave for a specific enemy type.
   *
   * @param type The enemy type to set the wave for.
   * @param wave The wave number in which the enemy becomes available.
   */
  void set_starting_wave(BaseEnemy::EnemyType type, int wave);

  /*
   *@brief remove enemies to be deleted from the enemies list
   */
  // call this before move_enemies() in gameloop
  void filter_enemies();

  /*
   * @brief Move all enemies by calling `move_next` on each enemy
   */
  void move_enemies();

private:
  std::list<std::pair<BaseEnemy::EnemyType, int>> tickets;
  std::unordered_map<BaseEnemy::EnemyType, int> starting_waves;
  std::vector<std::shared_ptr<BaseEnemy>> enemies;
};
