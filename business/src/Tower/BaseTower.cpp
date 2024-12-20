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
