#include "Components/SidebarItem.hpp"
#include <iostream>
#include "SFML/Graphics/Rect.hpp"
#include "Utils/FontFactory.hpp"

SidebarItem::SidebarItem(std::function<std::string(void)> text_generator,
                         std::string icon_path)
    : text_generator(text_generator) {
  // Initialize the bg
  if (!bg_texture.loadFromFile("./assets/textures/sidebar/item_bg.png")) {
    std::cerr << "Failed to load file: " << icon_path << std::endl;
    exit(1);
  }
  bg.setTexture(bg_texture);
  bg.setScale(4, 4);
  // Initialize the icon
  if (!icon_texture.loadFromFile(icon_path)) {
    std::cerr << "Failed to load file: " << icon_path << std::endl;
    exit(1);
  }
  icon.setTexture(icon_texture);

  // Set the scale
  auto bounds = icon.getLocalBounds();
  icon.setScale(ICON_LEN / bounds.width, ICON_LEN / bounds.height);

  // Initialize the font
  font = FontFactory::get_instance().get_primary_font();
  text.setFont(font);

  // Initialize the text
  text.setCharacterSize(25);

  // Initiate the string with the default value
  text.setString(text_generator());
}

sf::FloatRect SidebarItem::get_global_bounds() const {
  return bg.getGlobalBounds();
}

void SidebarItem::set_position(unsigned x, unsigned y) {
  bg.setPosition(x, y - 10);
  icon.setPosition(x + 10, y);
  text.setPosition(x + 10 + icon.getGlobalBounds().width + ICON_TEXT_MARGIN, y);
}
void SidebarItem::handle_events(EventData data) {}
void SidebarItem::render(RenderData ren) {
  ren.window->draw(bg);
  ren.window->draw(icon);
  ren.window->draw(text);
}
void SidebarItem::update(UpdateData) { text.setString(text_generator()); }
