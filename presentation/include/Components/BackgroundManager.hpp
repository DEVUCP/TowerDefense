#pragma once

#include "Interfaces/Widget.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class BackgroundManager : public Widget {
public:
  BackgroundManager() = default;
  ~BackgroundManager() = default;

  /*
   * @brief Load the background
   *
   * @param image Path to the image to load
   * @param window The window to scale the image to
   */
  void load_img(const std::string& image,
                std::shared_ptr<sf::RenderTarget> window);
  void load_img(std::string&& image, std::shared_ptr<sf::RenderTarget> window);

  /*
   * @brief private overrided functions
   */
  void handle_events(sf::Event) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;

private:
  sf::Sprite background;
  sf::Texture image;
};
