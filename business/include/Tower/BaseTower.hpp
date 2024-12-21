#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Upgrade.hpp"
#include "Map/BaseTile.hpp"
#include "Utils/Drawable.hpp"
#include "Utils/Vector.hpp"

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
  BaseTower(int i, int j, unsigned range, unsigned attack_speed = 1);

  /**
   * @brief Initiates an attack on the specified enemy.
   *
   * @param enemy A shared pointer to the enemy to attack.
   *
   * @details Checks if the enemy is within range and performs the attack logic.
   */
  void init_attack(std::shared_ptr<BaseEnemy> enemy);

  /**
   * @brief Checks if the enemy is within the tower's attack range.
   *
   * @param enemy A shared pointer to the enemy to check.
   * @return True if the enemy is within range, otherwise false.
   */
  bool in_range(std::shared_ptr<Map> map);

  /**
   * @brief Upgrades the tower based on the selected upgrade index.
   *
   * @param upgrade_index The index of the upgrade to apply.
   *
   * @details The upgrade improves the tower's attributes, such as range or damage,
   * based on the selected upgrade option.
   */
  void upgrade(int upgrade_index);

  /**
   * @brief Calculates the selling price of the tower.
   *
   * @return The sell price, including the base price and a portion of the applied upgrade costs.
   */
  int get_sell_price();

private:
  Vector<int> position;           // The position of the tower on the map.
  float range;                    // The attack range of the tower.
  float damage;                   // The attack damage of the tower.
  unsigned attack_speed;                   // The attack speed of the tower.
  std::shared_ptr<BaseTile> tile; // The tile the tower is on
  std::shared_ptr<Upgrade> offer_upgrades; // The upgrades available for the tower.
  std::shared_ptr<Upgrade> upgrades;      // The upgrades currently applied to the tower.
  std::string sprite;             // The visual representation of the tower.
  std::string rotation;           // The rotation state of the tower's sprite.
};
