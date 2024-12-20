#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Upgrade.hpp"
#include "Utils/Drawable.hpp"

/**
 * @brief Represents the base functionality of a tower in the game.
 *
 * Towers attack enemies, have a specific range, can be upgraded, 
 * and can be sold for a price based on their current upgrades.
 */
class BaseTower : public Drawable {
public:
  /**
   * @brief Constructor
   *
   * Initializes all member variables and sets up the base properties of the tower.
   */
  BaseTower();

  void init_attack(std::shared_ptr<BaseEnemy> enemy);

  bool in_range(std::shared_ptr<BaseEnemy> enemy);

  void upgrade(int upgrade_index);

  int get_sell_price();

private:
  std::shared_ptr<Upgrade> offer_upgrades;
  std::shared_ptr<Upgrade> upgrades;
  std::string rotation;
  Vector<int> position;           // The position of the tower on the map.
  float range;                    // The attack range of the tower.
  float damage;                   // The attack damage of the tower.
  std::string sprite;             // The visual representation of the tower.
};
