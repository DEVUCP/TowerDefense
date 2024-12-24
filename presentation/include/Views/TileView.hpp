#pragma once

#include "Interfaces/Clickable.hpp"
#include "Interfaces/Widget.hpp"
#include "Map/BaseTile.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
class TileView : public Clickable, public Widget {
public:
  TileView(std::shared_ptr<BaseTile> tile);
  virtual ~TileView() = default;

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::RectangleShape shape;
  std::shared_ptr<BaseTile> tile;
};
