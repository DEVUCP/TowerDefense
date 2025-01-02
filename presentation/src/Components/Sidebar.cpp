#include "Components/Sidebar.hpp"
#include <memory>
#include <string>
#include "Components/SFXPlayer.hpp"
#include "Components/SidebarItem.hpp"
#include "Components/SidebarTowerButton.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Tower/BaseTower.hpp"
#include "Views/BuildableTileView.hpp"
#include "iostream"

std::vector<std::pair<BaseTower::TowerType, std::string>> Sidebar::towers_info =
    {
        {BaseTower::ArcheryTower, "./assets/textures/towers/ArcheryTower.png"},
        {BaseTower::CatapultTower,
         "./assets/textures/towers/CatapultTower.png"},
        {BaseTower::ElectroTower, "./assets/textures/towers/ElectroTower.png"},
        {BaseTower::SlingshotTower,
         "./assets/textures/towers/SlingshotTower.png"},
        {BaseTower::OrbTower, "./assets/textures/towers/OrbTower.png"},
        {BaseTower::CrossbowTower,
         "./assets/textures/towers/CrossbowTower.png"},
};
Sidebar::Sidebar() {
  init_sidebar_bg();
  init_content();

  show_upgrade_buttons = false;
  init_tower_buttons();
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

  init_item(
      lives, "./assets/textures/sidebar/lives.png",
      []() {
        auto lvl = Game::get_instance().get_level();
        return std::to_string(lvl->get_lives());
      },
      100);
  init_item(
      coins, "./assets/textures/sidebar/coins.png",
      []() {
        auto lvl = Game::get_instance().get_level();
        return std::to_string(lvl->get_coins());
      },
      200);
}

void Sidebar::handle_events(EventData data) {
  if (target != nullptr) {
    if (!show_upgrade_buttons) {
      for (auto& twr : twr_btns) twr->handle_events(data);
    } else {
      upgrade_button->handle_events(data);
      sell_button->handle_events(data);
    }
  }
}

void Sidebar::render(RenderData ren) {
  ren.window->draw(sidebar_bg);
  lives->render(ren);
  coins->render(ren);

  if (target != nullptr) {
    if (!show_upgrade_buttons) {
      for (auto& twr_btn : twr_btns) twr_btn->render(ren);
    } else {
      upgrade_button->render(ren);
      sell_button->render(ren);
    }
  }
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

void Sidebar::show_upgrades() {
  auto tile = std::static_pointer_cast<BuildableTileView>(target);
  auto tower = tile->get_tower_view()->get_tower();

  if (tower->get_level() < tower->get_upgrades_count()) {
    upgrade_button->set_text("upgrade\n      for\n    " +
                             std::to_string(tower->get_upgrade_price()));
  } else {
    upgrade_button->set_text("max\nlevel");
  }

  sell_button->set_text("sell\n  for\n   " +
                        std::to_string(tower->get_sell_price()));

  show_upgrade_buttons = true;
}

void Sidebar::hide_upgrades() { show_upgrade_buttons = false; }

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

  upgrade_button = std::make_shared<TextButton>(
      "upgrade", x_start + cell_width, y_start + 150, 35,
      StandardButton::ButtonSize::XLARGE, StandardButton::ButtonType::SQUARE);
  upgrade_button->set_handler([this]() {
    auto tile = std::static_pointer_cast<BuildableTileView>(target);
    if (tile->upgrade_tower()) {
      target->set_selected(false);
      target = nullptr;
      SFXPlayer::get_instance().play(SFXPlayer::TOWER_BUILD);
    } else {
      target->set_selected(false);
      target = nullptr;
      // TODO: Replace with failed to upgrade sound
      // SFXPlayer::get_instance().play(SFXPlayer::TOWER_BUILD);
    }
  });

  upgrade_button->transform_text(0, -30 * 2);

  sell_button = std::make_shared<TextButton>(
      "sell", x_start + cell_width, y_start + 150 + 260, 35,
      StandardButton::ButtonSize::XLARGE, StandardButton::ButtonType::SQUARE);
  sell_button->set_handler([this]() {
    auto tile = std::static_pointer_cast<BuildableTileView>(target);
    tile->sell_tower();
    target->set_selected(false);
    target = nullptr;
    // TODO: Replace with tower destroying sound
    SFXPlayer::get_instance().play(SFXPlayer::TOWER_BUILD);
  });

  sell_button->transform_text(0, -30 * 2);

  int index = 0;
  for (auto& [type, path] : towers_info) {
    // Calculate row and column based on index
    int row = index / grid_width;
    int column = index % grid_width;

    // Compute x and y positions
    int x = x_start + column * cell_width + (column != 0 ? TOWERS_OFFSET : 0);
    int y = y_start + static_cast<int>(row * cell_height * vertical_spacing);

    auto twn_btn = std::make_shared<SidebarTowerButton>(
        x, y, path, BaseTower::get_buy_price(type));
    twn_btn->set_handler([this, type]() {
      if (target->get_tile()->get_type() != BaseTile::Buildable) return;
      auto converted = std::dynamic_pointer_cast<BuildableTileView>(target);
      if (converted->build_tower(type)) {
        target->set_selected(false);
        target = nullptr;
        SFXPlayer::get_instance().play(SFXPlayer::TOWER_BUILD);
      } else {
        target->set_selected(false);
        target = nullptr;
        // TODO: Replace with failed to builed sound
        // SFXPlayer::get_instance().play(SFXPlayer::TOWER_BUILD);
      }
    });

    twr_btns.push_back(twn_btn);
    index++;
  }
}
