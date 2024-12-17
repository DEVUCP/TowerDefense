#pragma once
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/Button.hpp"
#include "Components/Page.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MainMenu/Title.hpp"

class MainMenu : public Page {
public:
  MainMenu(unsigned width, unsigned height);

  /*
   * Overrided functions
   */
  void on_pause() override;
  void on_unpause() override;
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;

private:
  BackgroundManager background;
  Title title;
  std::shared_ptr<Button> play_btn;
  std::shared_ptr<Button> about_btn;
  std::shared_ptr<Button> mute_button;
};
