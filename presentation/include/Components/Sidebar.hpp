#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Font.hpp"

class Sidebar : public Widget {
public:
  Sidebar();

  /*
   * Overrided Functions
   */
  void handle_events(EventData data);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  void init_sidebar_bg();
  void init_content();

private:
  unsigned lives;
  unsigned enemies_on_board;
  unsigned enemies_on_total;
  sf::Sprite sidebar_bg;
  sf::Texture sidebar_texture;
  sf::Font font;
  sf::Text lives_t;
  sf::Text enemies_t;
  sf::Text score_t;
};
