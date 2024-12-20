#pragma once

#include "Utils/Vector.hpp"

/**
 * Invariant: origin will represent the origin (top-left most point)
 */
class Collidable {
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

private:
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
  Vector<float> position;
  union {
    Vector<float> size;
    float width, height;
  };
};
