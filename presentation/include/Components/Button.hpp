#pragma once
#include <functional>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

class Button {
public:
  Button();  // TODO: Initialze the button + types for Sizes/Types (don't know
             // yet)
  /*
   * @brief handle click event on this button
   */
  void on_click();

  /*
   * @brief Check if the button is hovered
   */
  bool is_hovered(sf::Vector2f point) const;

  /*
   * @brief Set a callback to run when the button is clicked
   */
  void set_handler(std::function<void(void)> new_handler);

private:
  std::function<void(void)> handler;
  sf::Sprite bg;
};
