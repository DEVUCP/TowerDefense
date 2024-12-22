#pragma once

#include "Interfaces/Widget.hpp"
#include "Map/BaseTile.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
class TileView : public Widget {
public:
  TileView(std::shared_ptr<BaseTile> tile);
  ~TileView() = default;

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update();

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::RectangleShape shape;
  std::shared_ptr<BaseTile> tile;
};
