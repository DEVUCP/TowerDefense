#pragma once

#include "Components/Button.hpp"
#include "SFML/Graphics/Texture.hpp"

#define DEFAULT_FONT_SIZE 40
#define LARGE_FONT_SIZE 70
#define BUTTON_ICON_COLOR 164, 146, 95

class IconButton : public Button {
public:
  IconButton(std::string path, std::string path_hover, unsigned x, unsigned y,
             Button::ButtonSize, Button::ButtonType);

  ~IconButton() = default;

  /*
   * @brief Change the button icon
   */
  void set_icon_texture(std::string path, std::string path_hover);
};
