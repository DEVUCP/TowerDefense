#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

class Button : public Widget {
public:
  enum class ButtonSize {
    LARGE,
    DEFAULT,
  };

  enum class ButtonType {
    RECT,
    SQUARE,
  };

public:
  /*
   * @brief Constructor
   *
   * @param x The x position of the button
   * @param y The y position of the button
   * @param size The size of the button
   * @param type The type of the button
   */
  Button(unsigned x, unsigned y, ButtonSize size, ButtonType type);

  /*
   * @brief handle click event on this button
   */
  void on_click();

  /*
   * @brief Set a callback to run when the button is clicked
   */
  void set_handler(std::function<void(void)> new_handler);

  /*
   * Overrided Functions
   */
  virtual void handle_events(sf::Event);
  virtual void render(std::shared_ptr<sf::RenderTarget> window);
  virtual void update();

private:
  /*
   * @brief Check if the button is hovered
   */
  bool is_hovered(sf::Vector2f point) const;

protected:
  sf::Texture texture;
  sf::Sprite bg;

private:
  std::function<void(void)> handler;
  ButtonType type;
  ButtonSize size;
  static std::unordered_map<
      ButtonType,
      std::unordered_map<ButtonSize, std::pair<std::string, std::string>>>
      images;
};
