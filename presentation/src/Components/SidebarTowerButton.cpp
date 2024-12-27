#include "Components/SidebarTowerButton.hpp"
#include <iostream>

SidebarTowerButton::SidebarTowerButton(unsigned x, unsigned y,
                                       std::string tower_path) {
  if (!bg_texture.loadFromFile("./assets/textures/sidebar/tower_bg.png")) {
    std::cerr << "Failed to load tower background" << std::endl;
    exit(1);
  }
  bg.setTexture(bg_texture);
  bg.setPosition(x, y);

  // Scale
  auto bounds = bg.getGlobalBounds();
  bg.setScale(120.f / bounds.width, 120.f / bounds.height);
}
void SidebarTowerButton::handle_events(EventData data) {}
void SidebarTowerButton::render(RenderData ren) { ren.window->draw(bg); }
void SidebarTowerButton::update(UpdateData) {}

const sf::FloatRect SidebarTowerButton::getGlobalBounds() {
  return bg.getGlobalBounds();
}
