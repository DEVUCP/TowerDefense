#include "Components/BackgroundManager.hpp"
#include <iostream>
#include <memory>
#include "Enums/Event.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

BackgroundManager::BackgroundManager(BackgroundType type, unsigned target_width,
                                     unsigned target_height, bool on)
    : on{on} {
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

void BackgroundManager::render(RenderData ren) {
  if (on) ren.window->draw(background);
}

void BackgroundManager::handle_events(EventData) {}
void BackgroundManager::update() {}

void BackgroundManager::onEvent(Event evt) {
  switch (evt) {
    case Event::BG_DEFAULT_SWITCH:
      on = true;
      background.setTexture(image_default);
      break;
    case Event::BG_SHADOW_SWITCH:
      on = true;
      background.setTexture(image_shadow);
      break;
    case Event::BG_CLEAR:
      on = false;
      break;
    default:
      break;
  }
}
