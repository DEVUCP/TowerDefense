#include "Components/StandardButton.hpp"
#include "Components/IButton.hpp"

std::unordered_map<StandardButton::ButtonType,
                   std::unordered_map<StandardButton::ButtonSize,
                                      std::pair<std::string, std::string>>>
    StandardButton::images = {
        {ButtonType::RECT,
         {// Outer map entry for RECT
          {ButtonSize::LARGE,
           {"./assets/textures/buttons/Rect_Large.png",
            "./assets/textures/buttons/Rect_Large_Hover.png"}},
          {ButtonSize::DEFAULT,
           {"./assets/textures/buttons/Rect_Default.png",
            "./assets/textures/buttons/Rect_Default_Hover.png"}}}},
        {ButtonType::SQUARE,
         {// Outer map entry for SQUARE
          {ButtonSize::LARGE,
           {"./assets/textures/buttons/Square_Large.png",
            "./assets/textures/buttons/Square_Large_Hover.png"}},
          {ButtonSize::DEFAULT,
           {"./assets/textures/buttons/Square_Default.png",
            "./assets/textures/buttons/Square_Default_Hover.png"}}}}};

StandardButton::StandardButton(unsigned x, unsigned y, ButtonSize size,
                               ButtonType type)
    : IButton(x, y), size{size}, type{type} {
  init_image(images[type][size].first, images[type][size].second);
}
