#include "Tower/Upgrade.hpp"

Upgrade::Upgrade(std::string name, int cost, float range_increase, float damage_increase)
    : name(std::move(name)), cost(cost), range_increase(range_increase), damage_increase(damage_increase) {}

std::string Upgrade::get_name() const {
    return name;
}
