#pragma once

#include <memory>
#include "SFML/Graphics/RenderWindow.hpp"
struct RenderData {
  sf::Time dt;
  std::shared_ptr<sf::RenderWindow> window;
};
