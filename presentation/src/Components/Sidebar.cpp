#include "Components/Sidebar.hpp"
#include <memory>
#include <string>
#include "Components/SidebarItem.hpp"
#include "Components/SidebarTowerButton.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Tower/BaseTower.hpp"

std::vector<std::pair<BaseTower::TowerType, std::string>> Sidebar::towers_info =
    {
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
        {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
};
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

  // Initialize the tower buttons
  // TODO: Make this dynamic
  init_tower_buttons();
}

void Sidebar::handle_events(EventData data) {}

void Sidebar::render(RenderData ren) {
  ren.window->draw(sidebar_bg);
  lives->render(ren);
  coins->render(ren);

  // if (target != nullptr)
  for (auto& twr_btn : twr_btns) twr_btn->render(ren);
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

void Sidebar::init_tower_buttons() {
  auto col = GameSettings::get_instance().get_columns();
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto sidebar_rows = GameSettings::get_instance().get_sidebar_row_count();

  int sidebar_width = sidebar_rows * tile_len;
  int grid_width = 2;             // Number of columns in the grid
  int cell_width = 120;           // Width of each button (or cell) in the grid
  int cell_height = 120;          // Height of each button (or cell) in the grid
  float vertical_spacing = 1.2f;  // Spacing factor for vertical positioning

  // Calculate starting x and y for the grid
  int x_start = col * tile_len +
                (sidebar_width - grid_width * cell_width - TOWERS_OFFSET) / 2;
  int y_start = 400;

  int index = 0;
  for (auto& twr : towers_info) {
    // Calculate row and column based on index
    int row = index / grid_width;
    int column = index % grid_width;

    // Compute x and y positions
    int x = x_start + column * cell_width + (column != 0 ? TOWERS_OFFSET : 0);
    int y = y_start + static_cast<int>(row * cell_height * vertical_spacing);

    twr_btns.push_back(std::make_shared<SidebarTowerButton>(x, y, twr.second));
    index++;
  }
}
