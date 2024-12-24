#include "Interfaces/Clickable.hpp"
#include "Components/SFXPlayer.hpp"
#include "SFML/Graphics/Sprite.hpp"

Clickable::Clickable() : handler([]() {}) {}
void Clickable::on_click() { handler(); }

void Clickable::set_handler(std::function<void(void)> new_handler) {
  handler = new_handler;
}
bool Clickable::is_hovered(sf::Vector2f point, const sf::Sprite& sprite) const {
  return sprite.getGlobalBounds().contains(point.x, point.y);
}
