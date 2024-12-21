#include "Views/TileView.hpp"
#include <ctime>
#include <random>
#include "GameSettings.hpp"
#include "SFML/Graphics/Rect.hpp"

static std::vector<std::string> buildables = {
    "./assets/textures/tiles/BuildableTile1.png",
    "./assets/textures/tiles/BuildableTile2.png",
    "./assets/textures/tiles/BuildableTile3.png",
    "./assets/textures/tiles/BuildableTile4.png",
};
static std::vector<int> buildables_weights = {
    25, 1, 1, 1};  // Weights for each texture (must match buildables size)
static std::vector<std::string> nonbuildables = {

};
std::random_device rd;   // Non-deterministic random number generator
std::mt19937 gen(rd());  // Seed the generator

TileView::TileView(float x, float y) : x{x}, y{y} {
  std::discrete_distribution<> dist(buildables_weights.begin(),
                                    buildables_weights.end());
  texture.loadFromFile(buildables[dist(gen)]);
  sprite.setTexture(texture);
  sprite.setPosition(x, y);

  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto bounds = sprite.getLocalBounds();

  // sprite.setTextureRect(sf::IntRect(0, 127, 16, 127 + 16));
  sprite.setScale(tile_len / bounds.width, tile_len / bounds.height);
  // shape.setPosition(x, y);
  // shape.setSize(sf::Vector2f(60, 60));
  // shape.setFillColor(sf::Color::White);
}

void TileView::handle_events(EventData data) {}

void TileView::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(sprite);
}
void TileView::update() {}
