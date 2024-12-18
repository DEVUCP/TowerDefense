#pragma once

#include "Interfaces/EventData.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics.hpp"

#define DEFAULT_IMAGE_ASSET "./assets/background/Default.png"
#define SHADOW_IMAGE_ASSET "./assets/background/Shadow.png"

class BackgroundManager : public Widget {
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

private:
  /*
   * @brief Load the background
   *
   * @param image Path to the image to load
   * @param target_width The width of the window
   * @param target_height The height of the window
   */
  void load_img(std::string image, unsigned target_width,
                unsigned target_height);

private:
  sf::Sprite background;
  sf::Texture image;
};
