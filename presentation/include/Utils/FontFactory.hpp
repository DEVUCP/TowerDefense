#pragma once

#include <memory>
#include "SFML/Graphics.hpp"

class FontFactory {
public:
  static const std::string primary_font;

public:
  // Delete copying
  FontFactory(const FontFactory&) = delete;
  FontFactory& operator=(const FontFactory&) = delete;

  /**
   * @brief Get the one instance of the FontFactory
   */
  static FontFactory& get_instance();

  /**
   * @brief Return a font
   */
  sf::Font get_primary_font();

private:
  FontFactory() = default;  // < private constructor
};
