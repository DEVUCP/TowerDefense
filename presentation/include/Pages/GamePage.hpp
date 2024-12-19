#pragma once

#include "Components/Page.hpp"
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

private:
  std::vector<std::vector<std::shared_ptr<TileView>>> map;
  sf::RectangleShape shape;
};
