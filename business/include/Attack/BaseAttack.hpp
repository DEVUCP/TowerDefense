#pragma once

#include <string>
#include "Utils/Drawable.hpp"
#include "Utils/Moveable.hpp"
/**
 * @class BaseAttack
 * @brief Represent the base class for all attacks to inherit
 *
 * @note Most of the logic will be done by the callbacks in `Moveable`
 */
class BaseAttack : public Moveable, Drawable {
public:
  /**
   * @brief Constructor
   *
   * @note Must call Moveable, and Drawable constructor
   */
  BaseAttack(float x, float y, float velocity, Vector<float> target,
             const std::string& sprite, int damage);

  /**
   * @brief Check if the element is to be removed
   *
   * @details Getter for `to_be_removed`
   */
  bool is_to_be_removed();

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
};
