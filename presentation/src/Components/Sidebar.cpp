#include "Components/Sidebar.hpp"
#include <memory>
#include <string>
#include "Components/SidebarItem.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"

Sidebar::Sidebar() {
  init_sidebar_bg();
  init_content();
}

void Sidebar::init_sidebar_bg() {
  if (!sidebar_texture.loadFromFile("./assets/textures/sidebar/bg.png"))
    exit(1);
  sidebar_bg.setTexture(sidebar_texture);
  auto h = GameSettings::get_instance().get_size().y;
  auto sidebar_row = GameSettings::get_instance().get_sidebar_row_count();
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto col = GameSettings::get_instance().get_columns();
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
  int i = 0;
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto col = GameSettings::get_instance().get_columns();
  auto sidebar_len =
      GameSettings::get_instance().get_sidebar_row_count() * tile_len;
  // lives_t.setString("Lives: 100");
  // coins_t.setString("Coins: 30");
  // score_t.setString("Score: 20XP");
  // for (auto& txt : texts) {
  //   txt->setFont(font);
  //   txt->setCharacterSize(30);
  //   txt->setFillColor(sf::Color::White);
  //   txt->setPosition(
  //       col * tile_len + (sidebar_len - txt->getLocalBounds().width) / 2.f,
  //       50 * i + 75);
  //   i++;
  // }

  init_item(
      lives, "./assets/textures/sidebar/lives.png",
      []() {
        auto lvl = Game::get_instance().get_level();
        return "lives: " + std::to_string(lvl->get_lives());
      },
      100);
  init_item(
      coins, "./assets/textures/sidebar/coins.png",
      []() {
        auto lvl = Game::get_instance().get_level();
        return "Coins: " + std::to_string(lvl->get_coins());
      },
      200);
}

void Sidebar::handle_events(EventData data) {}

void Sidebar::render(RenderData ren) {
  ren.window->draw(sidebar_bg);
  lives->render(ren);
  coins->render(ren);
}
void Sidebar::update(UpdateData dat) {
  lives->update(dat);
  coins->update(dat);
}

void Sidebar::init_item(std::shared_ptr<SidebarItem>& item,
                        std::string icon_path,
                        std::function<std::string(void)> func, int y) {
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto col = GameSettings::get_instance().get_columns();
  auto sidebar_len =
      GameSettings::get_instance().get_sidebar_row_count() * tile_len;
  item = std::make_shared<SidebarItem>(func, icon_path);
  auto bounds = item->get_global_bounds();
  item->set_position(col * tile_len + (sidebar_len - bounds.width) / 2.f, y);
}

void Sidebar::set_tile_target(std::shared_ptr<TileView> tile) { target = tile; }
