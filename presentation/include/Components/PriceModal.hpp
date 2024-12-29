#pragma once

#include "Interfaces/Clickable.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SidebarItem.hpp"
#include "Text.hpp"

class PriceModal : public Widget {
public:
  PriceModal(unsigned x, unsigned y, int price);

  /**
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief Returns true if it is currently visible, false otherwise
   */
  bool is_visible();

  /**
   * @brief Sets the visibility of the price modal
   */
  void set_visibility(bool);

  /**
   * @brief Return the global bounds
   */
  const sf::FloatRect getGlobalBounds();

private:
  sf::Sprite bg;
  sf::Texture bg_texture;
  sf::Sprite icon;
  sf::Texture icon_texture;
  std::shared_ptr<Text> money_text;
  bool show;
};
