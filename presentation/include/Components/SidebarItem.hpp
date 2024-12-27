#pragma once

#include <functional>
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Rect.hpp"

class SidebarItem : public Widget {
public:
  static constexpr int ICON_LEN = 32;
  static constexpr int ICON_TEXT_MARGIN = 10;

public:
  SidebarItem(std::function<std::string(void)>, std::string icon_path);

  /**
   * Overrided Functions
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief get global bounds
   */
  sf::FloatRect get_global_bounds() const;

  /**
   * @brief Set the position of the elements
   */
  void set_position(unsigned x, unsigned y);

private:
  sf::Font font;
  sf::Text text;
  sf::Texture icon_texture;
  sf::Sprite icon;
  std::function<std::string(void)> text_generator;
  sf::Texture bg_texture;
  sf::Sprite bg;
};
