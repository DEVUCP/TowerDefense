#include "Components/Sidebar.hpp"
#include "GameSettings.hpp"
#include "SFML/System/Vector3.hpp"
#include "Utils/FontFactory.hpp"

Sidebar::Sidebar() {
  init_sidebar_bg();
  init_content();
}

void Sidebar::init_sidebar_bg() {
  if (!sidebar_texture.loadFromFile("./assets/textures/sidebar/bg.png"))
    exit(1);
  sidebar_bg.setTexture(sidebar_texture);
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto col = GameSettings::get_instance().get_columns();
  auto h = GameSettings::get_instance().get_size().y;
  auto sidebar_row = GameSettings::get_instance().get_sidebar_row_count();
  sidebar_bg.setPosition(col * tile_len, 0);
  auto bounds = sidebar_bg.getLocalBounds();
  float actual_width = bounds.width;
  float actual_height = bounds.height;

  // Calculate scale factors
  float scale_x = tile_len * sidebar_row / actual_width;
  float scale_y = h / actual_height;

  // Apply scaling
  sidebar_bg.setScale(scale_x, scale_y);
}

void Sidebar::init_content() {
  font = FontFactory::get_instance().get_primary_font();
  std::vector<sf::Text*> texts = {&lives_t, &enemies_t, &score_t};
  int i = 0;
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto col = GameSettings::get_instance().get_columns();
  for (auto& txt : texts) {
    txt->setFont(font);
    txt->setCharacterSize(30);
    txt->setFillColor(sf::Color::White);
    txt->setPosition(col * tile_len + 15, 50 * i + 25);
    i++;
  }
  lives_t.setString("Lives: 100");
  enemies_t.setString("Enemies: 20/30");
  score_t.setString("Score: 20XP");
}

void Sidebar::handle_events(EventData data) {}

void Sidebar::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(sidebar_bg);
  window->draw(lives_t);
  window->draw(enemies_t);
  window->draw(score_t);
}
void Sidebar::update() {}
