#pragma once
#include <memory>
#include "Interfaces/EventData.hpp"
#include "Interfaces/RenderData.hpp"
#include "Interfaces/UpdateData.hpp"
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
  virtual void handle_events(EventData data) = 0;

  /*
   * @brief Render the widget
   */
  virtual void render(RenderData) = 0;

  /*
   * @brief Update the widget state
   */
  virtual void update(UpdateData) = 0;
};
