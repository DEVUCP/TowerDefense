#include "Components/Button.hpp"
#include <functional>
#include "SFML/System/Vector2.hpp"

void Button::on_click() { handler(); }

bool Button::is_hovered(sf::Vector2f point) const {
  return bg.getGlobalBounds().contains(point.x, point.y);
}

void Button::set_handler(std::function<void(void)> new_handler) {
  handler = new_handler;
}
