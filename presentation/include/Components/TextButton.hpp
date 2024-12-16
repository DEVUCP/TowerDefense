#pragma once

#include <memory>
#include "Components/Button.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
class TextButton : public Button {
public:
  TextButton(std::string text, unsigned x, unsigned y, Button::ButtonSize);

  ~TextButton() = default;

  /*
   * @brief Render the text above the rectangle in the middle of the rect
   */
  void render(std::shared_ptr<sf::RenderTarget> window) override;

private:
  sf::Text text;
  sf::Font font;
};
