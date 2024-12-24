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

static std::vector<std::string> buildables = {
    "./assets/textures/tiles/Buildables/1.png",
    "./assets/textures/tiles/Buildables/2.png",
    "./assets/textures/tiles/Buildables/3.png",
};

static std::vector<std::string> nonbuildables = {
    "./assets/textures/tiles/Nonbuildables/1.png",
    "./assets/textures/tiles/Nonbuildables/2.png",
    "./assets/textures/tiles/Nonbuildables/3.png",
};
static std::vector<std::string> enemypath = {
    "./assets/textures/tiles/Enemypath/1.png",
    "./assets/textures/tiles/Enemypath/2.png",
    "./assets/textures/tiles/Enemypath/3.png",
};
std::random_device rd;   // Non-deterministic random number generator
std::mt19937 gen(rd());  // Seed the generator

TileView::TileView(std::shared_ptr<BaseTile> tile) : tile{tile} {
  std::vector<std::string>* tiles = nullptr;

  switch (tile->get_type()) {
    case BaseTile::Buildable:
      tiles = &buildables;
      break;
    case BaseTile::NonBuildable:
      tiles = &nonbuildables;
      break;
    case BaseTile::EnemyPath:
      tiles = &enemypath;
      break;
    default:
      throw std::runtime_error("Not enough tiles");
  }
  std::uniform_int_distribution<> dist(0, tiles->size() - 1);
  texture.loadFromFile(tiles->operator[](dist(gen)));
  sprite.setTexture(texture);
  auto pos = tile->get_position();
  sprite.setPosition(pos.x, pos.y);

  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto bounds = sprite.getLocalBounds();

  sprite.setScale(tile_len / bounds.width, tile_len / bounds.height);

  if (tile->get_type() == BaseTile::Buildable) {
    set_handler([tile]() {
      // auto converted = std::dynamic_pointer_cast<BuildableTile>(tile);
      // converted->set_tower(nullptr);
      std::cout << "hello" << std::endl;
    });
  }
}

void TileView::handle_events(EventData data) {
  if (data.event.type == sf::Event::MouseButtonPressed &&
      is_hovered(sf::Vector2f{static_cast<float>(data.mouse_pointer.x),
                              static_cast<float>(data.mouse_pointer.y)},
                 sprite))
    on_click();
}

void TileView::render(RenderData ren) { ren.window->draw(sprite); }
void TileView::update(UpdateData dat) {}
