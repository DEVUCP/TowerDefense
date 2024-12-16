#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Text.hpp"

class Title : public Widget {
public:
  /*
   * @brief Constructor
   */
  Title();

  /*
   * @brief Overrided functions
   */
  void handle_events(sf::Event);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  Button play_button;
};
