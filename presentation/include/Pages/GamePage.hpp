#pragma once

#include "Components/Page.hpp"
#include "Components/Sidebar.hpp"
#include "Views/EnemyView.hpp"
#include "Views/TileView.hpp"

class GamePage : public Page {
public:
  GamePage(unsigned width, unsigned height);

  /*
   * Overrided functions
   */
  void on_pause() override;
  void on_unpause() override;
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;

private:
  /*
   * @Initialize the map
   */
  void init_map();

  /*
   * @initialize the sidebar
   */
  void init_sidebar();

private:
  std::vector<std::vector<std::shared_ptr<TileView>>> map;
  std::vector<std::shared_ptr<EnemyView>> enemies;
  std::shared_ptr<Sidebar> sidebar;
};
