#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Text.hpp"

class Title : public Widget {
public:
  /*
   * @brief Constructor
   */
  Title(std::string text, unsigned target_width, unsigned target_height);

  /*
   * @brief Overrided functions
   */
  void handle_events(EventData) override;
  void render(RenderData) override;
  void update() override;

  /*
   * @brief Set The text
   */
  void set_text(std::string text);

private:
  sf::Text title_text;
  sf::Font font;
};
