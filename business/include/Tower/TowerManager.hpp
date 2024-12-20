#pragma once

#include <vector>
#include <memory>
#include "Tower/BaseTower.hpp"
#include "Enemy/BaseEnemy.hpp"

class TowerManager {
public:
    void add_tower(std::shared_ptr<BaseTower> tower);

    void remove_tower(std::shared_ptr<BaseTower> tower);

    void upgrade_tower(std::shared_ptr<BaseTower> tower, int upgrade_index);

private:
    std::vector<std::shared_ptr<BaseTower>> towers; // List of all towers managed by the TowerManager.
};
