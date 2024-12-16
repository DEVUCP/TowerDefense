#include "Utils/TextBuilder.hpp"

TextBuilder::TextBuilder() { reset(); }

TextBuilder &TextBuilder::setSize(int size) {
  text.setCharacterSize(size);
  return *this;
}

TextBuilder &TextBuilder::setText(const std::string &value) {
  text.setString(value);
  return *this;
}

TextBuilder &TextBuilder::setText(std::string &&value) {
  text.setString(std::move(value));
  return *this;
}

TextBuilder &TextBuilder::setColor(sf::Color color) {
  text.setFillColor(color);
  return *this;
}

TextBuilder &TextBuilder::setPosition(sf::Vector2f vec) {
  text.setPosition(vec);
  return *this;
}

TextBuilder &TextBuilder::setFont(sf::Font font) {
  text.setFont(font);
  return *this;
}

sf::Text TextBuilder::build() { return text; }

void TextBuilder::reset() {
  text.setFillColor(sf::Color::Black);
  text.setCharacterSize(8);
  text.setString("Builder not set yet!!!");
}
