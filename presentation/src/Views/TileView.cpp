#include "Views/TileView.hpp"
#include <ctime>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include "GameSettings.hpp"
#include "Map/BaseTile.hpp"
#include "Map/BuildableTile.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"
#include "Tower/Towers/IonPrism.hpp"

static std::vector<std::string> nonbuildables = {};
static std::vector<std::string> enemypath = {};

TileView::TileView(std::shared_ptr<BaseTile> tile) : tile{tile} {}

void TileView::handle_events(EventData data) {
  if (data.event.type == sf::Event::MouseButtonPressed &&
      is_hovered(sf::Vector2f{static_cast<float>(data.mouse_pointer.x),
                              static_cast<float>(data.mouse_pointer.y)},
                 sprite))
    on_click();
}

void TileView::render(RenderData ren) { ren.window->draw(sprite); }
void TileView::update(UpdateData dat) {}

std::shared_ptr<BaseTile> TileView::get_tile() const { return tile; }

void TileView::load_sheets(const std::vector<std::string>& tiles) {
  std::random_device rd;   // Non-deterministic random number generator
  std::mt19937 gen(rd());  // Seed the generator
  std::uniform_int_distribution<> dist(0, tiles.size() - 1);
  texture.loadFromFile(tiles[dist(gen)]);
  sprite.setTexture(texture);
  auto pos = tile->get_position();
  sprite.setPosition(pos.x, pos.y);

  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto bounds = sprite.getLocalBounds();

  sprite.setScale(tile_len / bounds.width, tile_len / bounds.height);
}
