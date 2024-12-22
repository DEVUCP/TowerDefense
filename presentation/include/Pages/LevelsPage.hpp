#pragma once
#include <memory>
#include "Components/IButton.hpp"
#include "Components/LevelButton.hpp"
#include "Components/Page.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

class LevelsPage : public Page {
public:
  LevelsPage(unsigned w, unsigned h);

  /*
   * Overrided functions
   */
  void on_pause() override;
  void on_unpause() override;
  void handle_events(EventData) override;
  void render(RenderData) override;
  void update() override;

private:
  unsigned level_count;
  std::vector<std::unique_ptr<LevelButton>> levels_btns;
  std::shared_ptr<IButton> go_back;
  std::shared_ptr<MuteButton> mute_button;
};
