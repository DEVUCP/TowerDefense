#pragma once

#include "Interfaces/EventData.hpp"
#include "Interfaces/Observer.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics.hpp"

#define DEFAULT_IMAGE_ASSET "./assets/background/Default.png"
#define SHADOW_IMAGE_ASSET "./assets/background/Shadow.png"

class BackgroundManager : public Widget, public Observer {
public:
  enum BackgroundType { DEFAULT, SHADOW };

public:
  BackgroundManager(BackgroundType, unsigned, unsigned, bool on = true);
  ~BackgroundManager() = default;

  /*
   * @brief private overrided functions
   */
  void handle_events(EventData) override;
  void render(RenderData) override;
  void update() override;
  void onEvent(Event) override;

private:
  /*
   * @brief Load all background textures
   */
  void load_textures();

private:
  sf::Sprite background;
  sf::Texture image_default;
  sf::Texture image_shadow;
  bool on;
};
