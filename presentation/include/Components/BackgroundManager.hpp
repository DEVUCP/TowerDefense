#pragma once

#include "Interfaces/EventData.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics.hpp"

class BackgroundManager : public Widget {
public:
  BackgroundManager() = default;
  ~BackgroundManager() = default;

  /*
   * @brief Load the background
   *
   * @param image Path to the image to load
   * @param target_width The width of the window
   * @param target_height The height of the window
   */
  void load_img(std::string image, unsigned target_width,
                unsigned target_height);

  /*
   * @brief private overrided functions
   */
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;

private:
  sf::Sprite background;
  sf::Texture image;
};
