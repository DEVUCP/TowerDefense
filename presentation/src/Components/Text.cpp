#include "Components/Text.hpp"
#include <cassert>
#include <iostream>
#include "Interfaces/EventData.hpp"
#include "Utils/FontFactory.hpp"
#include "Utils/TextBuilder.hpp"

Text::Text(std::string _text, int font_size, sf::Color color, unsigned x, unsigned y) {
  text.setFillColor(color);
  set_text(_text);
  text.setCharacterSize(font_size);

  font = FontFactory::get_instance().get_primary_font();
  text.setFont(font);

  text.setPosition(x - text.getLocalBounds().width / 2, y - text.getLocalBounds().height / 2);
}

void Text::handle_events(EventData) {}

void Text::render(RenderData ren) { ren.window->draw(text); }

void Text::update(UpdateData dat) {}

void Text::set_text(std::string _text) { text.setString(_text); }
