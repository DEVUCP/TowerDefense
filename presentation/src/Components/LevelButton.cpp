#include "Components/LevelButton.hpp"
#include "Components/IButton.hpp"
#include "Utils/FontFactory.hpp"

LevelButton::LevelButton(unsigned x, unsigned y, int num)
    : IButton(x, y), num{num} {
  init_image("./assets/buttons/Dummy.png", "./assets/buttons/Dummy.png");
  bg.setScale(1.5, 1.5);

  text.setFillColor(sf::Color(LEVEL_NUM_COLOR));
  text.setString(std::to_string(num));
  text.setCharacterSize(LEVEL_NUM_FONT_SIZE);

  font = FontFactory::get_instance().get_primary_font();
  text.setFont(font);

  sf::FloatRect bgBounds =
      bg.getGlobalBounds();  // Get global bounds of the sprite
  sf::FloatRect textBounds = text.getLocalBounds();  // Get bounds of the text

  // Calculate centered position for the text
  float textX =
      bgBounds.left + (bgBounds.width - textBounds.width) / 2 - textBounds.left;
  float textY =
      bgBounds.top + (bgBounds.height - textBounds.height) / 4 - textBounds.top;

  // Set the position of the text
  text.setPosition(textX, textY);
}

void LevelButton::render(std::shared_ptr<sf::RenderTarget> window) {
  IButton::render(window);
  window->draw(text);
}
