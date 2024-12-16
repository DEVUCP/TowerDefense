#include "Utils/FontFactory.hpp"
#include "SFML/Graphics/Font.hpp"

const std::string FontFactory::primary_font =
    "./assets/fonts/Bungee-Regular.ttf";

FontFactory& FontFactory::get_instance() {
  static FontFactory fac;
  return fac;
}

sf::Font FontFactory::get_primary_font() {
  sf::Font font;
  if (!font.loadFromFile(primary_font)) exit(1);
  return font;
}
