#pragma once

#include <memory>
#include "Components/StandardButton.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#define DEFAULT_FONT_SIZE 40
#define LARGE_FONT_SIZE 70
#define BUTTON_TEXT_COLOR 164, 146, 95

class TextButton : public StandardButton {
public:
  TextButton(std::string text, unsigned x, unsigned y,
             StandardButton::ButtonSize, StandardButton::ButtonType);

  ~TextButton() = default;

  /*
   * @brief Render the text above the rectangle in the middle of the rect
   */
  void render(std::shared_ptr<sf::RenderTarget> window) override;

  /*
   * @brief Change button text
   */
  void set_text(std::string txt);

  /*
   * @brief Change button color
   */
  void set_color(sf::Color clr);

private:
  sf::Text text;
  sf::Font font;
};
