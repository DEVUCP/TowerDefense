#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Text.hpp"

class Text : public Widget {
public:
  /*
   * @brief Constructor
   */
  Text(std::string _text, int font_size, sf::Color color, unsigned x, unsigned y);

  /*
   * @brief Overrided functions
   */
  void handle_events(EventData) override;
  void render(RenderData) override;
  void update(UpdateData) override;

  /*
   * @brief Set The text
   */
  void set_text(std::string _text);

private:
  sf::Text text;
  sf::Font font;
};
