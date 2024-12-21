#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
class TileView : public Widget {
public:
  TileView(float x, float y);
  ~TileView() = default;

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  float x;
  float y;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::RectangleShape shape;
};
