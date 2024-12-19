#pragma once

#include "Utils/Vector.cpp"

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
   * @brief Sets enable to true
   */
  void enable_collision();

  /**
   * @brief Sets enable to false
   */
  void disable_collision();

private:
  bool enabled;
  Vector<float> position;
  union {
    Vector<float> size;
    float width, height;
  };
};