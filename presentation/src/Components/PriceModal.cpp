#include "Components/PriceModal.hpp"
#include <iostream>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"

PriceModal::PriceModal(unsigned x, unsigned y, int price) {
  show = false;

  if (!bg_texture.loadFromFile("./assets/textures/sidebar/item_bg.png")) {
    std::cerr << "Failed to load price modal background" << std::endl;
    exit(1);
  }
  bg.setTexture(bg_texture);
  bg.setPosition(x, y);

  bg.setScale(4, 4);

  bg.setPosition(x, y - 10);

  if (!icon_texture.loadFromFile("./assets/textures/sidebar/coins.png")) {
    std::cerr << "Failed to load file: " << "./assets/textures/sidebar/coins.png" << std::endl;
    exit(1);
  }
  icon.setTexture(icon_texture);

  // Set the scale
  auto bounds = icon.getLocalBounds();
  icon.setScale(SidebarItem::ICON_LEN / bounds.width,
                SidebarItem::ICON_LEN / bounds.height);

  icon.setPosition(x, y);

  money_text = std::make_shared<Text>(std::to_string(price), 25, sf::Color::White, x + (bg.getGlobalBounds().width) / 2, y + (bg.getGlobalBounds().height) / 2 - 20);
}

void PriceModal::handle_events(EventData data) { }

void PriceModal::render(RenderData ren) {
  if(!show) return;

  ren.window->draw(bg);
  ren.window->draw(icon);
  money_text->render(ren);
}

void PriceModal::update(UpdateData) {}

void PriceModal::set_visibility(bool visibility) {
  show = visibility;
}

bool PriceModal::is_visible() {
  return show;
}


const sf::FloatRect PriceModal::getGlobalBounds() {
  return bg.getGlobalBounds();
}
