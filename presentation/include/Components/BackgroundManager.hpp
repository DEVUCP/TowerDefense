#pragma once

#include "Enums/Events/BackgroundEvents.hpp"
#include "Interfaces/EventData.hpp"
#include "Interfaces/Observer.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics.hpp"

#define DEFAULT_IMAGE_ASSET "./assets/background/Default.png"
#define SHADOW_IMAGE_ASSET "./assets/background/Shadow.png"

class BackgroundManager : public Widget, Observer<BackgroundEvents> {
public:
  enum BackgroundType { DEFAULT, SHADOW };

public:
  BackgroundManager(BackgroundType, unsigned, unsigned);
  ~BackgroundManager() = default;

  /*
   * @brief private overrided functions
   */
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;
  void onEvent(BackgroundEvents) override;

private:
  /*
   * @brief Load all background textures
   */
  void load_textures();

private:
  sf::Sprite background;
  sf::Texture image_default;
  sf::Texture image_shadow;
};
