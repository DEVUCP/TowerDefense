#pragma once

#include "Interfaces/Widget.hpp"
class TileView : public Widget {
public:
  TileView(float x, float y);

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
};
