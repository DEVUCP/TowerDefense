#pragma once
#include <iostream>
#include <list>
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/IButton.hpp"
#include "Components/LevelButton.hpp"
#include "Components/Page.hpp"
#include "Components/Title.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class LevelsPage : public Page {
public:
  LevelsPage(unsigned w, unsigned h);

  /*
   * Overrided functions
   */
  void on_pause() override;
  void on_unpause() override;
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;

private:
  unsigned level_count;
  std::vector<std::unique_ptr<LevelButton>> levels_btns;
  std::shared_ptr<IButton> go_back;
  std::shared_ptr<IButton> mute_button;
};
