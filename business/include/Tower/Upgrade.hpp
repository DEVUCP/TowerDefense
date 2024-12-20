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

    /**
     * @brief Gets the name of the upgrade.
     * 
     * @return The name of the upgrade.
     */
    std::string get_name() const;

    /**
     * @brief Gets the cost of the upgrade.
     * 
     * @return The cost of the upgrade.
     */
    int get_cost() const;

    /**
     * @brief Gets the range increase provided by the upgrade.
     * 
     * @return The range increase value.
     */
    float get_range_increase() const;

    /**
     * @brief Gets the damage increase provided by the upgrade.
     * 
     * @return The damage increase value.
     */
    float get_damage_increase() const;

private:
    std::string name;        // The name of the upgrade.
    int cost;                // The cost of the upgrade.
    float range_increase;    // The increase in range provided by the upgrade.
    float damage_increase;   // The increase in damage provided by the upgrade.
};
