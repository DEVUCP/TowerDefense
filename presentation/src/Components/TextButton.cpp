#include "Components/TextButton.hpp"
#include "Components/Button.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "Utils/FontFactory.hpp"

TextButton::TextButton(std::string str, unsigned x, unsigned y, ButtonSize size,
                       ButtonType type)
    : Button(x, y, size, type) {
  text.setFillColor(sf::Color(BUTTON_TEXT_COLOR));
  text.setString(str);
  text.setCharacterSize(size == ButtonSize::LARGE ? LARGE_FONT_SIZE
                                                  : DEFAULT_FONT_SIZE);

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

TextButton::TextButton(std::string str, unsigned x, unsigned y,
                       sf::Texture texture, sf::Texture texture_hover)
    : Button(x, y, texture, texture_hover) {
  text.setFillColor(sf::Color(BUTTON_TEXT_COLOR));
  text.setString(str);
  text.setCharacterSize(size == ButtonSize::LARGE ? LARGE_FONT_SIZE
                                                  : DEFAULT_FONT_SIZE);

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

void TextButton::set_text(std::string txt) { text.setString(txt); }
