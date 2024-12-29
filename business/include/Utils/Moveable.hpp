#pragma once

#include "Utils/Positionable.hpp"
#include "Utils/Vector.hpp"

/**
 * @class Moveable
 * @brief Represents an abstraction of all moving objects in the game
 */
class Moveable : virtual public Positionable {
public:
  /**
   * @brief Constructor
   */
  Moveable(float x, float y, float velocity, Vector<float> destination);

  /**
   * @brief Update position to next step towerds destination point with given
   * speed
   *
   * @details Use vector arithmetic to get next direction
   * @details If reached to destination, call `on_reach`
   * @details If out of board, call `on_out_of_board`
   */
  void move_next();

  /**
   * @brief Update the direction to which the object is moving
   *
   * @details The interface provide the ability to adjust velcoity as well
   */
  void update_dest(Vector<float> destination);

  /**
   * @brief Check if an object is out of board of not
   *
   * @details Use GameSettings::get_instance().get_width() and get_height()
   */
  bool is_out_of_board();

  /**
   * @brief Getter for rotation
   */
  float get_rotation() const;

  /**
   * @brief Check if object has reached its destination
   */
  bool has_reached_destination() const;

  /**
   * @brief Change Velocity of an object
   */
  void set_velocity(int new_v);

protected:
  /**
   * @brief A callback to run when the object reaches its destination
   *
   * @details Inherited by the child classes to adjust their behavior.
   */
  virtual void on_reach() = 0;

  /**
   * @brief A callback to run when the object is out of board
   *
   * @details Inherited by the child classes to adjust their behavior
   */
  virtual void on_out_of_board() = 0;

  /**
   * @brief A callback to run when the object is moving
   *
   * @details Inherited by the child classes to adjust their behavior
   */
  virtual void on_move() = 0;

protected:
  Vector<float> dest_point;  // < represent the point the object is moving to
  Vector<float> unit_direction;  // < represent a unit vector in the direction
                                 // the object is moving
  float velocity;                // < the velocity by which the object is moving
};
