#include "Components/BackgroundManager.hpp"
#include <memory>
#include "Enums/Events/BackgroundEvents.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

BackgroundManager::BackgroundManager(BackgroundType type, unsigned target_width,
                                     unsigned target_height) {
  load_textures();
  background.setTexture(image_default);
  background.setPosition(0, 0);
  background.setScale(
      static_cast<float>(target_width) / image_default.getSize().x,
      static_cast<float>(target_height) / image_default.getSize().y);
}

void BackgroundManager::load_textures() {
  if (!image_default.loadFromFile("./assets/background/Default.png")) exit(1);
  if (!image_shadow.loadFromFile("./assets/background/Shadow.png")) exit(1);
}

void BackgroundManager::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(background);
}

void BackgroundManager::handle_events(EventData) {}
void BackgroundManager::update() {}

void BackgroundManager::onEvent(BackgroundEvents evt) {
  switch (evt) {
    case DEFAULT_SWITCH:
      background.setTexture(image_default);
      break;
    case SHADOW_SWITCH:
      background.setTexture(image_shadow);
      break;
    case CLEAR:
      // TODO: Figure out what to do
      break;
  }
}
