#pragma once

#include <string>
#include "Utils/Vector.hpp"
class Drawable {
  /**
   * @brief Constructor
   */
  Drawable(const std::string& sprite, Vector<float> size, float rotation);

  /**
   * @brief Getter for size
   */
  const Vector<float>& get_size() const;

  /**
   * @brief Getter for sprite
   */
  const std::string& get_sprite() const;

  /**
   * @brief Getter for rotation
   */
  const float get_rotation() const;

  /**
   * @brief Set rotation
   */
  void set_rotation(float);

private:
  Vector<float> size;
  std::string sprite;
  float rotation;  // < the direction represented by the angle between direction
                   // and x-axis
};
