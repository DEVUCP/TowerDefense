#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class TextBuilder {
public:
  TextBuilder();

  TextBuilder &setText(const std::string &);
  TextBuilder &setText(std::string &&);
  TextBuilder &setColor(sf::Color);
  TextBuilder &setSize(int);
  TextBuilder &setFont(sf::Font);
  TextBuilder &setPosition(sf::Vector2f);
  sf::Text build();

private:
  void reset();

private:
  sf::Text text;
};
