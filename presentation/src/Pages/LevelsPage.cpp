#include "Pages/LevelsPage.hpp"
#include <memory>
#include <vector>
#include "Components/IconButton.hpp"
#include "Components/LevelButton.hpp"
#include "Components/MusicPlayer.hpp"
#include "Game.hpp"
#include "Widgets/MuteButton.hpp"

LevelsPage::LevelsPage(unsigned w, unsigned h) : Page(w, h) {
  // Initia
  level_count = Game::get_instance().get_level()->get_level_count();

  const int ROW_COUNT = 5;                 // 5 levels per row
  const int startx = 440, starty = 400;    // Starting position
  const int offsetx = 250, offsety = 200;  // Spacing between buttons
  // Load the buttons
  for (int i = 0; i < level_count; i++) {
    int column = i % ROW_COUNT;  // Column index (0 to 4)
    int row = i / ROW_COUNT;     // Row index
    auto btn =
        std::make_unique<LevelButton>(startx + column * offsetx,  // X-position
                                      starty + row * offsety,     // Y-position
                                      i + 1);
    btn->set_handler([this, i]() {
      Game::get_instance().init_level(i + 1);
      notify_observers(Event::GAME_PAGE_SWITCH);
    });
    levels_btns.push_back(std::move(btn));  // Level number
  }

  // Initialize the go back button
  go_back =
      std::make_shared<IconButton>("./assets/buttons/GoBack.png",
                                   "./assets/buttons/GoBack_Hover.png", 60, 60);
  go_back->set_handler([this]() { notify_observers(Event::GO_BACK_SWITCH); });

  // Initialize the mute button
  mute_button = std::make_shared<MuteButton>(60, h - 60);
}

void LevelsPage::on_pause() {}
void LevelsPage::on_unpause() {
  notify_observers(Event::BG_DEFAULT_SWITCH);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::MAIN_MUSIC);
  mute_button->check_status();
}

void LevelsPage::handle_events(EventData evt) {
  for (auto& btn : levels_btns) btn->handle_events(evt);
  go_back->handle_events(evt);
  mute_button->handle_events(evt);
}

void LevelsPage::update(UpdateData dat) { mute_button->check_status(); }

void LevelsPage::render(RenderData ren) {
  for (auto& btn : levels_btns) btn->render(ren);
  go_back->render(ren);
  mute_button->render(ren);
}
