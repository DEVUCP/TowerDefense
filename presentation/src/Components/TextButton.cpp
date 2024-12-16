#include "Components/TextButton.hpp"
#include "Components/Button.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "Utils/FontFactory.hpp"

TextButton::TextButton(std::string str, unsigned x, unsigned y, ButtonSize size,
                       ButtonType type)
    : Button(x, y, size, type) {
  text.setFillColor(sf::Color(164, 146, 95));
  text.setString(str);
  text.setCharacterSize(size == ButtonSize::LARGE ? 75 : 45);

  font = FontFactory::get_instance().get_primary_font();
  text.setFont(font);

  sf::FloatRect bgBounds =
      bg.getGlobalBounds();  // Get global bounds of the sprite
  sf::FloatRect textBounds = text.getLocalBounds();  // Get bounds of the text

  // Calculate centered position for the text
  float textX =
      bgBounds.left + (bgBounds.width - textBounds.width) / 2 - textBounds.left;
  float textY =
      bgBounds.top + (bgBounds.height - textBounds.height) / 2 - textBounds.top;

  // Set the position of the text
  text.setPosition(textX, textY);
}

void TextButton::render(std::shared_ptr<sf::RenderTarget> window) {
  Button::render(window);
  window->draw(text);
}
