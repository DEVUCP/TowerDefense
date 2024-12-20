#include "Tower/TowerManager.hpp"
#include <iostream>
void TowerManager::add_tower(std::shared_ptr<BaseTower> tower) {
    towers.push_back(tower);
    // TODO: Implement adding a tower to the tile position
    // will need a getter for get_position() ?
    // Vector<float> position = tower->get_position();
}

void TowerManager::remove_tower(std::shared_ptr<BaseTower> tower) {
    auto it = std::remove(towers.begin(), towers.end(), tower);
    if (it != towers.end()) {
        towers.erase(it, towers.end());
        std::cout << "Tower removed!" << std::endl;
    } else {
        std::cout << "Tower not found for removal!" << std::endl;
    }
}
