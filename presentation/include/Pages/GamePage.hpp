#pragma once

#include <memory>
#include "Components/Page.hpp"
#include "Components/Sidebar.hpp"
#include "Interfaces/Clickable.hpp"
#include "Tower/BaseTower.hpp"
#include "Views/EnemyView.hpp"
#include "Views/TileView.hpp"
#include "Views/TowerView.hpp"

class GamePage : public Page {
public:
  GamePage(unsigned width, unsigned height);

  /*
   * Overrided functions
   */
  void on_pause() override;
  void on_unpause() override;
  void handle_events(EventData) override;
  void render(RenderData) override;
  void update(UpdateData) override;

  /**
   * @brief Set the clicked on tiled as the selected_tile
   */
  void set_selected(std::shared_ptr<TileView> tile_view);

private:
  /*
   * @brief Initialize the map
   */
  void init_map();

  /*
   * @brief initialize the sidebar
   */
  void init_sidebar();

  /**
   * @brief Build a tower
   */
  void build_tower(float x, float y, BaseTower::TowerType);

private:
  std::vector<std::vector<std::shared_ptr<TileView>>> map;
  std::vector<std::shared_ptr<EnemyView>> enemies;
  std::vector<std::shared_ptr<TowerView>> towers;
  std::shared_ptr<Sidebar> sidebar;
  std::shared_ptr<TileView> selected_tile;
};
