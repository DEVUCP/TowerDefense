#include "Tower/BaseTower.hpp"
#include "Tower/Upgrade.hpp"
#include <iostream>

#define BASE_DAMAGE 1.0f
#define BASE_RANGE 1.0f

BaseTower::BaseTower()
    : Drawable(sprite, Vector<float>(0, 0)), position({0, 0}), range(BASE_RANGE), damage(BASE_DAMAGE), sprite(""), rotation("") {
    // Initialize upgrades
    offer_upgrades = std::make_shared<Upgrade>("Default Upgrade", 100, 10.0f, 5.0f);
    upgrades = nullptr;
}

void BaseTower::init_attack(std::shared_ptr<BaseEnemy> enemy) {
    if (in_range(enemy)) {
        std::cout << "Attacking enemy at position: " << enemy->get_position()  << std::endl;
        enemy->invoke_damage(damage) ;
        // Implement attack logic here
    }
}

bool BaseTower::in_range(std::shared_ptr<BaseEnemy> enemy) {
  Vector<float> enemy_position = enemy->get_position()->get_position();
    float distance = std::sqrt(std::pow(position.x - enemy_position.x, 2) + 
                               std::pow(position.y - enemy_position.y, 2));
    return distance <= range;
}

void BaseTower::upgrade(int upgrade_index) {
    // Apply the upgrade based on the index
    if (offer_upgrades) {
        range += offer_upgrades->get_range_increase();
        std::cout << "Upgrade applied: " << offer_upgrades->get_name() << std::endl;
        upgrades = offer_upgrades; // Assume applying the first upgrade
    } else {
        std::cout << "No upgrades available to apply!" << std::endl;
    }
}

