#pragma once
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/IButton.hpp"
#include "Components/Page.hpp"
#include "Components/Title.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

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
  Title title;
  std::shared_ptr<IButton> play_btn;
  std::shared_ptr<IButton> about_btn;
  std::shared_ptr<IButton> mute_button;
};
