#include "Components/TextButton.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "Utils/FontFactory.hpp"

TextButton::TextButton(std::string str, unsigned x, unsigned y, ButtonSize size,
                       ButtonType type)
    : StandardButton(x, y, size, type) {
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

void TextButton::render(RenderData ren) {
  StandardButton::render(ren);
  ren.window->draw(text);
}

void TextButton::transform_text(int x, int y) {
  int start_x = text.getPosition().x;
  int start_y = text.getPosition().y;

  text.setPosition(start_x + x, start_y + y);
}

void TextButton::set_text(std::string txt) { text.setString(txt); }
void TextButton::set_color(sf::Color clr) { text.setFillColor(clr); }
