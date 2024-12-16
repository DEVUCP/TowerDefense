#include "Components/Button.hpp"
#include <functional>
#include "SFML/System/Vector2.hpp"

std::unordered_map<
    Button::ButtonType,
    std::unordered_map<Button::ButtonSize, std::pair<std::string, std::string>>>
    Button::images = {
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

Button::Button(unsigned x, unsigned y, ButtonSize size, ButtonType type)
    : size(size), type(type) {
  texture.loadFromFile(images[type][size].first);
  bg.setTexture(texture);
  bg.setPosition(x - bg.getGlobalBounds().width / 2.f,
                 y - bg.getGlobalBounds().height / 2.f);
}

void Button::on_click() { handler(); }

bool Button::is_hovered(sf::Vector2f point) const {
  return bg.getGlobalBounds().contains(point.x, point.y);
}

void Button::set_handler(std::function<void(void)> new_handler) {
  handler = new_handler;
}

void Button::handle_events(sf::Event) {}
void Button::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(bg);
}
void Button::update() {}
