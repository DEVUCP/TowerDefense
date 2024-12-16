#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

/*
 * @class Widget
 * @brief Represents any class that can be rendered on game
 */
class Widget {
public:
  ~Widget() = default;
  /*
   * @brief Handle events
   */
  virtual void handle_events(sf::Event) = 0;

  /*
   * @brief Render the widget
   */
  virtual void render(std::shared_ptr<sf::RenderTarget> window) = 0;

  /*
   * @brief Update the widget state
   */
  virtual void update() = 0;
};
