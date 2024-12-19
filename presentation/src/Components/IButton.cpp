#include "Components/IButton.hpp"
#include <functional>
#include <iostream>
#include "Components/SFXPlayer.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"

IButton::IButton(unsigned x, unsigned y) : x{x}, y{y}, handler([]() {}) {}

void IButton::init_image(std::string t1, std::string t2) {
  texture.loadFromFile(t1);
  texture_hover.loadFromFile(t2);
  bg.setTexture(texture);
  bg.setPosition(x - bg.getGlobalBounds().width / 2.f,
                 y - bg.getGlobalBounds().height / 2.f);
}
void IButton::on_click() {
  SFXPlayer::get_instance().play(SFXPlayer::BUTTON_CLICK);
  handler();
}

bool IButton::is_hovered(sf::Vector2f point) const {
  return bg.getGlobalBounds().contains(point.x, point.y);
}

void IButton::set_handler(std::function<void(void)> new_handler) {
  handler = new_handler;
}

void IButton::handle_events(EventData evt) {
  if (is_hovered({static_cast<float>(evt.mouse_pointer.x),
                  static_cast<float>(evt.mouse_pointer.y)})) {
    bg.setTexture(texture_hover);
    if (evt.event.type == sf::Event::MouseButtonPressed) {
      on_click();
    }
  } else {
    bg.setTexture(texture);
  }
}
void IButton::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(bg);
}
void IButton::update() {}
