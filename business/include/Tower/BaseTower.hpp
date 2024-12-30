#pragma once

#include <chrono>
#include <memory>
#include "Enemy/BaseEnemy.hpp"
#include "Map/BaseTile.hpp"
#include "Utils/Vector.hpp"

/**
 * @brief Represents the base functionality of a tower in the game.
 *
 * Towers attack enemies, have a specific range, can be upgraded,
 * and can be sold for a price based on their current upgrades.
 */
class BaseTower {
public:
  enum TowerType {
    ArcheryTower,
    ElectroTower,
    SlingshotTower,
    CatapultTower,
  };

public:
  /**
   * @brief Constructor
   *
   * @details Initializes all member variables and sets up the base properties
   * of the tower.
   */
  BaseTower(std::shared_ptr<BaseTile> tile, unsigned range, TowerType type,
            int price);
  /**
   * @brief Initiates an attack on the specified enemy.
   *
   * @param enemy A shared pointer to the enemy to attack.
   *
   * @details Checks if the enemy is within range and performs the attack logic.
   */
  void init_attack(std::shared_ptr<BaseEnemy> enemy);

  /**
   * @brief Returns all enemies in `range`
   *
   * @details Use BFS to consider all `EnemyPathTile` tiles in range. If it has
   * enemies, init an attack towards the first enemy there ()
   */
  std::vector<std::shared_ptr<BaseEnemy>> enemies_in_range();

  /**
   * @brief Upgrades the tower based on the selected upgrade index.
   *
   * @param upgrade_index The index of the upgrade to apply.
   *
   * @details The upgrade improves the tower's attributes, such as range or
   * damage, based on the selected upgrade option.
   */
  void upgrade(int upgrade_index);

  /**
   * @brief Calculates the selling price of the tower.
   *
   * @return The sell price, including the base price and a portion of the
   * applied upgrade costs.
   */
  int get_sell_price();

  /**
   * @brief Get tower's price.
   *
   * @return The base price of the tower.
   */
  static int get_buy_price(TowerType type);

  /**
   * @brief Get tower Type
   */
  TowerType get_type() const;

  /**
   * @brief Get position
   */
  Vector<float> get_position() const;

  /**
   * @brief Get the tower level
   */
  int get_level() const;

  /**
   * @brief Reset the tower shooting time
   */
  void reset_shoot_time();

  /**
   * @brief check if the tower can shoot now
   */
  bool can_shoot() const;

private:
  std::shared_ptr<BaseTile> tile;  // The tile this tower is on
  unsigned range;                  // The attack range of the tower.
  // std::shared_ptr<Upgrade>
  //     offer_upgrades;  // The upgrades available for the tower.
  // std::shared_ptr<Upgrade>
  //     upgrades;          // The upgrades currently applied to the tower.
  int lvl;         // < The greater the leve, the greater the power
  TowerType type;  // < The type
  unsigned shoot_rate;
  std::chrono::steady_clock::time_point last_shoot_time;  // Track last run time
};
