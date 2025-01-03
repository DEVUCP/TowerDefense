#include "Components/IButton.hpp"
#include <functional>
#include <iostream>
#include "Components/SFXPlayer.hpp"
#include "Interfaces/Clickable.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/System/Vector2.hpp"

IButton::IButton(unsigned x, unsigned y) : x{x}, y{y}, handler([]() {}) {}

void IButton::init_image(std::string t1, std::string t2) {
  if (!texture.loadFromFile(t1)) {
    std::cerr << "Failed to load texture: " << t1 << std::endl;
    exit(1);
  }
  if (!texture_hover.loadFromFile(t2)) {
    std::cerr << "Failed to load texture: " << t2 << std::endl;
    exit(1);
  }
  bg.setTexture(texture);
  bg.setPosition(x - bg.getGlobalBounds().width / 2.f,
                 y - bg.getGlobalBounds().height / 2.f);
}

void IButton::handle_events(EventData evt) {
  if (is_hovered({static_cast<float>(evt.mouse_pointer.x),
                  static_cast<float>(evt.mouse_pointer.y)},
                 bg)) {
    bg.setTexture(texture_hover);
    if (evt.event.type == sf::Event::MouseButtonPressed) {
      on_click();
    }
  } else {
    bg.setTexture(texture);
  }
}
void IButton::render(RenderData ren) { ren.window->draw(bg); }
void IButton::update(UpdateData dat) {}

void IButton::on_click() {
  SFXPlayer::get_instance().play(SFXPlayer::BUTTON_CLICK);
  Clickable::on_click();
}
