#pragma once

#include <string>

class Upgrade {
public:
    Upgrade(std::string name, int cost, float range_increase, float damage_increase);
private:
    std::string name;        // Name of the upgrade
    int cost;                // Cost to apply the upgrade
    float range_increase;    // Increase in tower range
    float damage_increase;   // Increase in tower damage
};
