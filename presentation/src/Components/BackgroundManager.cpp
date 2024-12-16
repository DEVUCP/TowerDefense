#include "Components/BackgroundManager.hpp"
#include <memory>
#include "SFML/Graphics/RenderTarget.hpp"

void BackgroundManager::load_img(std::string img, unsigned target_width,
                                 unsigned target_height) {
  if (!image.loadFromFile(img)) {
    exit(1);
  }
  background.setTexture(image);
  background.setPosition(0, 0);
  background.setScale(static_cast<float>(target_width) / image.getSize().x,
                      static_cast<float>(target_height) / image.getSize().y);
}

void BackgroundManager::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(background);
}

void BackgroundManager::handle_events(sf::Event) {}
void BackgroundManager::update() {}
