#include "Widgets/MainMenu/Title.hpp"
#include <cassert>
#include <iostream>
#include "Utils/TextBuilder.hpp"

Title::Title() {
  title_text.setFillColor(sf::Color::Yellow);
  title_text.setString("Bug Slayer");
  title_text.setCharacterSize(200);

  font.loadFromFile("assets/fonts/EnvyCodeRNerdFont.ttf");
  title_text.setFont(font);
}

void Title::handle_events(sf::Event) {}

void Title::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(title_text);
}

void Title::update() {}
