#include "Tower/TowerManager.hpp"
#include <iostream>
void TowerManager::add_tower(std::shared_ptr<BaseTower> tower) {
    towers.push_back(tower);
    // Vector<float> position = tower->get_position();
}

