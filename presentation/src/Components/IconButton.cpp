#include "Components/IconButton.hpp"
#include <iostream>
#include "Components/Button.hpp"
#include "SFML/Graphics/Texture.hpp"

IconButton::IconButton(std::string path, std::string path_hover, unsigned x,
                       unsigned y, Button::ButtonSize size,
                       Button::ButtonType type)
    : Button(x, y, size, type) {
  set_icon_texture(path, path_hover);
}

void IconButton::set_icon_texture(std::string path, std::string path_hover) {
  if (!texture.loadFromFile(path)) {
    std::cerr << "failed to load file: " << path << std::endl;
    exit(1);
  }
  if (!texture_hover.loadFromFile(path_hover)) {
    std::cerr << "failed to load file: " << path_hover << std::endl;
    exit(1);
  }
  bg.setTexture(texture);
}
