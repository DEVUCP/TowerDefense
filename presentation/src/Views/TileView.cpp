#include "Views/TileView.hpp"
#include <ctime>
#include <memory>
#include <random>
#include "GameSettings.hpp"
#include "Map/BaseTile.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"

TileView::TileView(std::shared_ptr<BaseTile> tile)
    : tile{tile}, selected(false) {
  init_selected();
}

void TileView::handle_events(EventData data) {
  if (data.event.type == sf::Event::MouseButtonPressed &&
      is_hovered(sf::Vector2f{static_cast<float>(data.mouse_pointer.x),
                              static_cast<float>(data.mouse_pointer.y)},
                 sprite))
    on_click();
}

void TileView::render(RenderData ren) {
  ren.window->draw(sprite);
  if (selected) ren.window->draw(selected_sprite);
}
void TileView::update(UpdateData dat) {
  if (selected) {
    selected_mng.next_sprite(selected_sprite);
  }
}

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

void TileView::init_selected() {
  selected_mng.load_sheet(selected_sprite, selected_texture,
                          "./assets/textures/tiles/selected.png");

  selected_mng.set_width(32);
  selected_mng.set_height(32);
  selected_mng.register_collection("C", 0, 4);
  selected_mng.set_collection("C");
  selected_mng.init_sprite_texture(selected_sprite);

  auto pos = tile->get_position();
  selected_sprite.setPosition(pos.x, pos.y);

  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto bounds = selected_sprite.getLocalBounds();
  selected_sprite.setScale(tile_len / bounds.width, tile_len / bounds.height);
}

void TileView::set_selected(bool value) { selected = value; }
