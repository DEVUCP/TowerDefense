#include "Tower/Upgrade.hpp"

Upgrade::Upgrade(std::string name, int cost, float range_increase,
                 float damage_increase)
    : name(std::move(name)),
      cost(cost),
      range_increase(range_increase),
      damage_increase(damage_increase) {}

std::string Upgrade::get_name() const { return name; }

int Upgrade::get_cost() const { return cost; }

float Upgrade::get_range_increase() const { return range_increase; }

float Upgrade::get_damage_increase() const { return damage_increase; }
