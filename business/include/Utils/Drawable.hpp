#pragma once

#include <string>
#include "Utils/Vector.hpp"
class Drawable {
  /**
   * @brief Constructor
   */
  Drawable(const std::string& sprite, Vector<float> size);

  /**
   * @brief Getter for size
   */
  const Vector<float>& get_size() const;

  /**
   * @brief Getter for sprite
   */
  const std::string& get_sprite() const;

private:
  Vector<float> size;
  std::string sprite;
};
