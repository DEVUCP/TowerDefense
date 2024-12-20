#pragma once

#include <vector>
#include <memory>
#include "Tower/BaseTower.hpp"
#include "Enemy/BaseEnemy.hpp"

/**
 * @brief Manages all towers in the game, handling their placement, upgrades, and interactions with enemies.
 */
class TowerManager {
public:
    /**
     * @brief Adds a new tower to the game.
     * 
     * @param tower The tower to be added.
     */
    void add_tower(std::shared_ptr<BaseTower> tower);

    /**
     * @brief Removes a tower from the game.
     * 
     * @param tower The tower to be removed.
     */
    void remove_tower(std::shared_ptr<BaseTower> tower);

    /**
     * @brief Updates all towers, including their attacks on enemies.
     * 
     * @param enemies The list of enemies in the game.
     */
    void update(std::vector<std::shared_ptr<BaseEnemy>>& enemies);

    /**
     * @brief Upgrades a specified tower.
     * 
     * @param tower The tower to upgrade.
     * @param upgrade_index The index of the upgrade to apply.
     */
    void upgrade_tower(std::shared_ptr<BaseTower> tower, int upgrade_index);

    /**
     * @brief Sells a tower and refunds the player.
     * 
     * @param tower The tower to sell.
     * @return The amount of money refunded.
     */
    int sell_tower(std::shared_ptr<BaseTower> tower);

private:
    std::vector<std::shared_ptr<BaseTower>> towers; // List of all towers managed by the TowerManager.
};
