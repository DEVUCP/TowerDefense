#pragma once

#include <memory>
#include <vector>
#include "Tower/BaseTower.hpp"

/**
 * @brief Manages all towers in the game, handling their placement,
 * upgrades, and interactions with enemies.
 */
class TowerManager {
public:
  /**
   * @brief Check the tower range
   *
   * @param map The map that holds the tiles to check against
   */
  void check_tower_range(std::shared_ptr<Map> map) const;

  /**
   * @brief Removes a tower from the game.
   *
   * @param tower The tower to be removed.
   */
  void remove_tower(std::shared_ptr<BaseTower> tower);

  /**
   * @brief Register a new tower to the game.
   *
   * @param tower The tower to be added.
   */
  void add_tower(std::shared_ptr<BaseTower> tower);

  /**
   * @brief Upgrades a specified tower.
   *
   * @param tower The tower to upgrade.
   * @param upgrade_index The index of the upgrade to apply.
   */
  void upgrade_tower(std::shared_ptr<BaseTower> tower);

  /**
   * @brief Sells a tower and refunds the player.
   *
   * @param tower The tower to sell.
   * @return The amount of money refunded.
   */
  int sell_tower(std::shared_ptr<BaseTower> tower);

private:
  std::vector<std::shared_ptr<BaseTower>>
      towers;  // List of all towers managed by the TowerManager.
};
