#include "Views/TileView.hpp"
#include <iostream>
#include "GameSettings.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

std::vector<sf::IntRect> enemy_paths = {
    sf::IntRect(0, 127, 16, 127 + 16),
    sf::IntRect(0, 127, 16, 127 + 16),
};

TileView::TileView(float x, float y) : x{x}, y{y} {
  texture.loadFromFile("./assets/sheets/TileSheet.png");
  sprite.setTexture(texture);
  sprite.setPosition(x, y);
  std::cout << x << " " << y << std::endl;

  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto bounds = sprite.getLocalBounds();

  sprite.setTextureRect(sf::IntRect(0, 127, 16, 127 + 16));
  sprite.setScale(tile_len / 16.f, tile_len / 16.f);
  // shape.setPosition(x, y);
  // shape.setSize(sf::Vector2f(60, 60));
  // shape.setFillColor(sf::Color::White);
}

void TileView::handle_events(EventData data) {}

void TileView::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(sprite);
}
void TileView::update() {}
