#include "Tower/TowerManager.hpp"
#include <iostream>
void TowerManager::add_tower(std::shared_ptr<BaseTower> tower) {
    towers.push_back(tower);
    // TODO: Implement adding a tower to the tile position
    // will need a getter for get_position() ?
    // Vector<float> position = tower->get_position();
}

