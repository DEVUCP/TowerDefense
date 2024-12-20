#pragma once

#include <vector>
#include <memory>
#include "Map/BaseTile.hpp"
class AttackManager {
public:
  /**
   * @brief Move all attacks, and check for each having reach an enemy
   *
   * @details use `hit` in the BaseAttack interface in all enemies in the tile
   * of that attack
   */
  void move_attacks();

private:
  std::vector<std::shared_ptr<BaseAttack>> attacks;
};
