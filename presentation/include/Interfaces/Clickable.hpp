#pragma once

#include <functional>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
class Clickable {
public:
  Clickable();
  /*
   * @brief handle click event on this button
   */
  virtual void on_click();
  /*
   * @brief Set a callback to run when the button is clicked
   */
  void set_handler(std::function<void(void)> new_handler);

protected:
  /*
   * @brief Check if the button is hovered
   */
  bool is_hovered(sf::Vector2f point, const sf::Sprite& sprite) const;

private:
  std::function<void(void)> handler;
};
