#pragma once

#include <memory>
#include <vector>
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

  /**
   * @brief Register an attack
   */
  void register_attack(std::shared_ptr<BaseAttack>);

  /**
   * @brief Remove an attack
   */
  void remove_attack(std::shared_ptr<BaseAttack>);

  /**
   * @brief Filter attacks with `to_be_removed`
   */
  void filter_attacks();

private:
  std::vector<std::shared_ptr<BaseAttack>> attacks;
};
