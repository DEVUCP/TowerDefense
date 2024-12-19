#include "Components/IconButton.hpp"
#include <iostream>
#include "SFML/Graphics/Texture.hpp"

IconButton::IconButton(std::string path, std::string path_hover, unsigned x,
                       unsigned y)
    : IButton(x, y) {
  init_image(path, path_hover);
}
