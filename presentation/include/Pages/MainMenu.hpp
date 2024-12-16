#pragma once
#include <memory>
#include <vector>
#include "Components/BackgroundManager.hpp"
#include "Components/Button.hpp"
#include "Components/Page.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MainMenu/Title.hpp"

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
  Title title;
  std::shared_ptr<Button> play_btn;
};
