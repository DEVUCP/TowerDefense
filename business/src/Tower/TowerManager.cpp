#include "Tower/TowerManager.hpp"
#include <iostream>
#include <algorithm>

// TODO: Implement any missing functionalities instead of cout-ing it

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

void TowerManager::update(std::vector<std::shared_ptr<BaseEnemy>>& enemies) {
    for (auto& tower : towers) {
        for (auto& enemy : enemies) {
            if (tower->in_range(enemy)) {
                tower->init_attack(enemy);
            }
        }
    }
}

void TowerManager::upgrade_tower(std::shared_ptr<BaseTower> tower, int upgrade_index) {
    if (std::find(towers.begin(), towers.end(), tower) != towers.end()) {
        tower->upgrade(upgrade_index);
        std::cout << "Tower upgraded!" << std::endl;
    } else {
        std::cout << "Tower not found for upgrade!" << std::endl;
    }
}

int TowerManager::sell_tower(std::shared_ptr<BaseTower> tower) {
    auto it = std::find(towers.begin(), towers.end(), tower);
    if (it != towers.end()) {
        int sell_price = tower->get_sell_price();
        towers.erase(it);
        std::cout << "Tower sold for: " << sell_price << std::endl;
        return sell_price;
    } else {
        std::cout << "Tower not found for selling!" << std::endl;
        return 0;
    }
}
