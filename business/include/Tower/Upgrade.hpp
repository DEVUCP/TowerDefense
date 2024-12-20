#pragma once

#include <string>

/**
 * @brief Represents an upgrade for a tower in the game.
 *
 * Upgrades enhance a tower's capabilities, such as increasing its range
 * or damage, at a specific cost.
 */
class Upgrade {
public:
    /**
     * @brief Constructor to initialize an upgrade.
     *
     * @param name The name of the upgrade.
     * @param cost The cost to apply the upgrade.
     * @param range_increase The increase in the tower's range when the upgrade is applied.
     * @param damage_increase The increase in the tower's damage when the upgrade is applied.
     */
    Upgrade(std::string name, int cost, float range_increase, float damage_increase);

    std::string get_name() const;
    int get_cost() const;
    float get_range_increase() const;
    float get_damage_increase() const;

private:
    std::string name;        // Name of the upgrade
    int cost;                // Cost to apply the upgrade
    float range_increase;    // Increase in tower range
    float damage_increase;   // Increase in tower damage
};
