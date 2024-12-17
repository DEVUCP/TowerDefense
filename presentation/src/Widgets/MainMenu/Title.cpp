#include "Widgets/MainMenu/Title.hpp"
#include <cassert>
#include <iostream>
#include "Interfaces/EventData.hpp"
#include "Utils/FontFactory.hpp"
#include "Utils/TextBuilder.hpp"

Title::Title(unsigned target_w, unsigned target_h) {
  title_text.setFillColor(sf::Color(253, 226, 148));
  title_text.setString("Bug Slayer");
  title_text.setCharacterSize(100);

  font = FontFactory::get_instance().get_primary_font();
  title_text.setFont(font);

  title_text.setPosition(
      target_w / 2.f - title_text.getLocalBounds().width / 2,
      target_h / 3.f - title_text.getLocalBounds().height / 2);
}

void Title::handle_events(EventData) {}

void Title::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(title_text);
}

void Title::update() {}
