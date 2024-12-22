#pragma once

#include "Components/IButton.hpp"

#define DEFAULT_FONT_SIZE 40
#define LARGE_FONT_SIZE 70
#define BUTTON_ICON_COLOR 164, 146, 95

class IconButton : public IButton {
public:
  IconButton(std::string path, std::string path_hover, unsigned x, unsigned y);

  ~IconButton() = default;
};
