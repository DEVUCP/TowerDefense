#pragma once

#include "Components/Page.hpp"
class LevelPage : public Page {
public:
  LevelPage(unsigned width, unsigned height);
  /*
   * Overrided functions
   */
  void on_pause() override;
  void on_unpause() override;
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;

private:
};
