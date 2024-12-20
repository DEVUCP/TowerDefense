#pragma once

#include <vector>
#include <memory>
#include "Tower/BaseTower.hpp"
#include "Enemy/BaseEnemy.hpp"

class TowerManager {
public:
    void add_tower(std::shared_ptr<BaseTower> tower);

    void remove_tower(std::shared_ptr<BaseTower> tower);

    void update(std::vector<std::shared_ptr<BaseEnemy>>& enemies);

    void upgrade_tower(std::shared_ptr<BaseTower> tower, int upgrade_index);

    int sell_tower(std::shared_ptr<BaseTower> tower);

private:
    std::vector<std::shared_ptr<BaseTower>> towers; // List of all towers managed by the TowerManager.
};
