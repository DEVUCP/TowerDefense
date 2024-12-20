#pragma once

#include <string>

class Upgrade {
public:
    Upgrade(std::string name, int cost, float range_increase, float damage_increase);

    std::string get_name() const;
    int get_cost() const;
    float get_range_increase() const;
private:
    std::string name;        // Name of the upgrade
    int cost;                // Cost to apply the upgrade
    float range_increase;    // Increase in tower range
    float damage_increase;   // Increase in tower damage
};
