#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "Interfaces/EventData.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

class IButton : public Widget {
public:
  /*
   * @brief Constructor
   *
   * @param x The x position of the button
   * @param y The y position of the button
   * @param size The size of the button
   * @param type The type of the button
   */
  IButton(unsigned x, unsigned y);

  /*
   * @brief handle click event on this button
   */
  virtual void on_click();

  /*
   * @brief Set a callback to run when the button is clicked
   */
  void set_handler(std::function<void(void)> new_handler);

  /*
   * Overrided Functions
   */
  virtual void handle_events(EventData) override;
  virtual void render(RenderData) override;
  virtual void update() override;

protected:
  void init_image(std::string texture_path, std::string texture_path_hover);

private:
  /*
   * @brief Check if the button is hovered
   */
  bool is_hovered(sf::Vector2f point) const;

protected:
  sf::Texture texture;
  sf::Texture texture_hover;
  sf::Sprite bg;

private:
  std::function<void(void)> handler;
  unsigned x, y;
};
