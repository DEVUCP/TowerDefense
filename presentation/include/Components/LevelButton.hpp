#pragma once

#include "Components/IButton.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Window.hpp"

#define LEVEL_NUM_COLOR 253, 226, 148
class LevelButton : public IButton {
public:
  LevelButton(unsigned x, unsigned y, int num);

  void render(std::shared_ptr<sf::RenderTarget> window) override;

private:
  int num;
  sf::Text text;
  sf::Font font;
};