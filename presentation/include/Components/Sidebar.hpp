#pragma once

#include <memory>

#include "Components/SidebarItem.hpp"
#include "Components/SidebarTowerButton.hpp"
#include "Interfaces/Widget.hpp"
#include "TextButton.hpp"
#include "Tower/BaseTower.hpp"
#include "Views/TileView.hpp"

class Sidebar : public Widget {
public:
  static constexpr unsigned TOWERS_OFFSET = 10;

public:
  Sidebar();

  /*
   * Overrided Functions
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief Set the target tile for the tower construction
   */
  void set_tile_target(std::shared_ptr<TileView> tile);

  /**
   * @brief Toggle the visibility of the upgrade buttons when a tile is clicked
   */
  void show_upgrades();
  void hide_upgrades();

private:
  void init_sidebar_bg();
  void init_content();
  void init_item(std::shared_ptr<SidebarItem>& item, std::string icon_path,
                 std::function<std::string(void)> func, int y);
  void init_tower_buttons();

private:
  sf::Sprite sidebar_bg;
  sf::Texture sidebar_texture;
  std::shared_ptr<SidebarItem> lives;
  std::shared_ptr<SidebarItem> coins;
  std::shared_ptr<TileView> target;
  std::vector<std::shared_ptr<SidebarTowerButton>> twr_btns;
  static std::vector<std::pair<BaseTower::TowerType, std::string>> towers_info;
  std::shared_ptr<TextButton> upgrade_button;
  std::shared_ptr<TextButton> sell_button;
  bool show_upgrade_buttons;
};
