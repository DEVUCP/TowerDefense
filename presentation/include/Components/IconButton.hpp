#pragma once

#include "Components/TextButton.hpp"
#include "SFML/Graphics/Texture.hpp"

#define DEFAULT_FONT_SIZE 40
#define LARGE_FONT_SIZE 70
#define BUTTON_ICON_COLOR 164, 146, 95

class IconButton : public StandardButton {
public:
  IconButton(std::string path, std::string path_hover, unsigned x, unsigned y,
             StandardButton::ButtonSize, StandardButton::ButtonType);

  ~IconButton() = default;

  /*
   * @brief Change the button icon
   */
  void set_icon_texture(std::string path, std::string path_hover);

  /*
   * Override
   */
  virtual void on_click();
};
