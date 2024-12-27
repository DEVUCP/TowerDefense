#pragma once

#include <memory>
#include "Components/SidebarItem.hpp"
#include "Interfaces/Widget.hpp"
#include "Views/TileView.hpp"

class Sidebar : public Widget {
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

private:
  void init_sidebar_bg();
  void init_content();
  void init_item(std::shared_ptr<SidebarItem>& item, std::string icon_path,
                 std::function<std::string(void)> func, int y);

private:
  sf::Sprite sidebar_bg;
  sf::Texture sidebar_texture;
  std::shared_ptr<SidebarItem> lives;
  std::shared_ptr<SidebarItem> coins;
  std::shared_ptr<TileView> target;
};
