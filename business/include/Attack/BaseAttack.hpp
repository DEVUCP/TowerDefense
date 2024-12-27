#pragma once

#include <memory>
#include <string>
#include "Enemy/BaseEnemy.hpp"
#include "Utils/Moveable.hpp"

/**
 * @class BaseAttack
 * @brief Represent the base class for all attacks to inherit
 *
 * @note Most of the logic will be done by the callbacks in `Moveable`
 */
class BaseAttack : public Moveable, public Collidable {
public:
  /**
   * @brief Constructor
   *
   * @note Must call Moveable
   */
  BaseAttack(float x, float y, float width, float height, float velocity,
             Vector<float> target, const std::string& sprite, int damage);

  /**
   * @brief Check if the element is to be removed
   *
   * @details Getter for `to_be_removed`
   */
  bool is_to_be_removed();

  /**
   * @brief Will call helper methods to detect collisions and apply them in
   * correct order.
   *
   * @details will be called by AttackManager after moving.
   */
  void check_collisions(std::shared_ptr<Map> map);

  /**
   * @brief Filter nearby tiles
   *
   * @details helper for check_collisions that returns vector of only the tiles
   * the attack is in that are enemypaths.
   */
  std::vector<std::shared_ptr<BaseTile>> filter_tiles(
      std::vector<std::shared_ptr<BaseTile>> nearby);

  /**
   * @brief get all nearby tiles
   *
   * @details helper for check_collisions that returns vector of any tiles that
   * are within collision points
   */
  std::vector<std::shared_ptr<BaseTile>> get_nearby_tiles(
      std::shared_ptr<Map> map);

  /**
   * @brief Check if the attack has hit an enemy
   *
   * @detials Use some collision detection algorithm such as AABA
   * @detials If it has found the enemy, call `on_hit`
   */
  bool hit(std::shared_ptr<BaseEnemy> enemy);

  /**
   * @brief A callback to run when the attack finds the enemy. Invoke damage to
   * that enemy
   */
  void on_hit();

  /**
   * @brief Getter for CurrentTile
   */
  std::shared_ptr<BaseTile> tile;

protected:
  // Inherited callbacks
  virtual void on_reach()
      override;  // Provide a default behavior of deleting the attack and
                 // invoking damange. This can be adjusted by subclasses
  virtual void on_out_of_board()
      override;  // Provide a default behavior of removing the attack. This can
                 // be adjusted by subclasses

private:
  bool to_be_removed;  // < a flag to indicate that this attack is to be
                       // removed, either because it's out of edge or because
                       // it's hit target
  int damage;
  std::shared_ptr<BaseTile> current_tile;
};
