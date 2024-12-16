#pragma once
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/Page.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class MainMenu : public Page {
public:
  MainMenu(unsigned width, unsigned height);

  /*
   * Overrided functions
   */
  void on_pause();
  void on_unpause();
  void handle_events(sf::Event);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  BackgroundManager background;
};
