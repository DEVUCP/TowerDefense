#include "Components/SidebarTowerButton.hpp"
#include <iostream>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"

SidebarTowerButton::SidebarTowerButton(unsigned x, unsigned y,
                                       std::string tower_path) {
  if (!bg_texture.loadFromFile("./assets/textures/sidebar/tower_bg.png")) {
    std::cerr << "Failed to load tower background" << std::endl;
    exit(1);
  }
  bg.setTexture(bg_texture);
  bg.setPosition(x, y);

  // Scale Bg
  auto bounds = bg.getGlobalBounds();
  bg.setScale(120.f / bounds.width, 120.f / bounds.height);

  // Initiate the tower bg
  if (!twr_texture.loadFromFile(tower_path)) {
    std::cerr << "Failed to load tower" << std::endl;
    exit(1);
  }
  twr.setTexture(twr_texture);
  twr.setTextureRect(sf::IntRect(0, 0, 64, 128));
  twr.setScale(0.8, 0.8);
  twr.setPosition(
      x + (bg.getGlobalBounds().width - twr.getGlobalBounds().width) / 2,
      y + (bg.getGlobalBounds().height - twr.getGlobalBounds().height) / 2 -
          15);
}
void SidebarTowerButton::handle_events(EventData data) {
  if (data.event.type == sf::Event::MouseButtonPressed &&
      is_hovered(sf::Vector2f{static_cast<float>(data.mouse_pointer.x),
                              static_cast<float>(data.mouse_pointer.y)},
                 bg)) {
    on_click();
  }
}
void SidebarTowerButton::render(RenderData ren) {
  ren.window->draw(bg);
  ren.window->draw(twr);
}
void SidebarTowerButton::update(UpdateData) {}

const sf::FloatRect SidebarTowerButton::getGlobalBounds() {
  return bg.getGlobalBounds();
}
