#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Text.hpp"

class Title : public Widget {
public:
  /*
   * @brief Constructor
   */
  Title(unsigned target_width, unsigned target_height);

  /*
   * @brief Overrided functions
   */
  void handle_events(sf::Event);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  sf::Text title_text;
  sf::Font font;
};
