#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
class SidebarTowerButton : public Widget {
public:
  SidebarTowerButton(unsigned x, unsigned y, std::string tower_path);

  /**
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief Return the global bounds
   */
  const sf::FloatRect getGlobalBounds();

private:
  sf::Sprite bg;
  sf::Texture bg_texture;
  sf::Sprite twr;
  sf::Texture twr_texture;
};
