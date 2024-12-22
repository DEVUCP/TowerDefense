#include "Components/Title.hpp"
#include <cassert>
#include <iostream>
#include "Interfaces/EventData.hpp"
#include "Utils/FontFactory.hpp"
#include "Utils/TextBuilder.hpp"

Title::Title(std::string text, unsigned target_w, unsigned target_h) {
  title_text.setFillColor(sf::Color(253, 226, 148));
  set_text(text);
  title_text.setCharacterSize(100);

  font = FontFactory::get_instance().get_primary_font();
  title_text.setFont(font);

  title_text.setPosition(
      target_w / 2.f - title_text.getLocalBounds().width / 2,
      target_h / 3.f - title_text.getLocalBounds().height / 2);
}

void Title::handle_events(EventData) {}

void Title::render(RenderData ren) { ren.window->draw(title_text); }

void Title::update(UpdateData dat) {}

void Title::set_text(std::string text) { title_text.setString(text); }
