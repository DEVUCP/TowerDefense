#pragma once

#include "Utils/Positionable.hpp"
#include "Utils/Vector.hpp"

/**
 * Invariant: origin will represent the origin (top-left most point)
 */
class Collidable : virtual public Positionable {
public:
  Collidable(float x, float y, float width, float height, bool enabled = true);

  /**
   * @brief Checks if collision points of given Collidable overlap with self
   * points
   */
  bool collide_with(const Collidable&);

  /**
   * @brief Checks if single point is within collision shape
   */
  bool point_colliding(Vector<float> point);

  /**
   * @brief Sets enable to true
   */
  void enable_collision();

  /**
   * @brief Sets enable to false
   */
  void disable_collision();

protected:
  /**
   * @brief Returns top left point coordinates
   */
  Vector<float> tl() const;

  /**
   * @brief Returns top right point coordinates
   */
  Vector<float> tr() const;

  /**
   * @brief Returns bottom left point coordinates
   */
  Vector<float> bl() const;

  /**
   * @brief Returns bottom right point coordinates
   */
  Vector<float> br() const;

private:
  bool enabled;
  union {
    Vector<float> size;
    float width, height;
  };
};
