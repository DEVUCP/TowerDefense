#include "Pages/WinPage.hpp"
#include <memory>

#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "Game.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

WinPage::WinPage(unsigned width, unsigned height)
    : Page(width, height), title("Level Complete", width, height) {
  unsigned start_x = width / 2, start_y = height / 2;
  int score_text_offset_y = -50;
  int buttons_offset_y = 100;
  int buttons_spacing_x = 160;
  int button_offset_multiplier = -1;

  score_text = std::make_shared<Text>(
      "Score: " + std::to_string(Game::get_instance().get_level()->get_score()),
      80, sf::Color::White, start_x, start_y + score_text_offset_y);

  restart_button = std::make_shared<IconButton>(
      "./assets/buttons/Restart.png", "./assets/buttons/Restart_Hover.png",
      start_x + buttons_spacing_x * button_offset_multiplier++,
      start_y + buttons_offset_y);
  restart_button->set_handler([this]() {
    Game::get_instance().init_level(
        Game::get_instance().get_level()->get_level_num());
    notify_observers(Event::GAME_PAGE_REPLACE);
  });

  continue_button = std::make_shared<IconButton>(
      "./assets/buttons/Play.png", "./assets/buttons/Play_Hover.png",
      start_x + buttons_spacing_x * button_offset_multiplier++,
      start_y + buttons_offset_y);
  continue_button->set_handler([this]() {
    if (Game::get_instance().get_level()->get_level_num() <
        Game::get_instance().get_level()->get_level_count()) {
      Game::get_instance().init_level(
          Game::get_instance().get_level()->get_level_num() + 1);
      notify_observers(Event::GAME_PAGE_REPLACE);
    } else {
      notify_observers(Event::GO_BACK_SWITCH);
    }
  });

  levels_button = std::make_shared<IconButton>(
      "./assets/buttons/Levels.png", "./assets/buttons/Levels_Hover.png",
      start_x + buttons_spacing_x * button_offset_multiplier++,
      start_y + buttons_offset_y);
  levels_button->set_handler(
      [this]() { notify_observers(Event::LEVEL_PAGE_SWITCH); });
}

void WinPage::on_pause() {}
void WinPage::on_unpause() {
  notify_observers(Event::BG_SHADOW_SWITCH);
  // TODO: Change to win music
  MusicPlayer::get_instance().set_current_music(MusicPlayer::LEVEL_MUSIC);
}

void WinPage::handle_events(EventData evt) {
  if (levels_button) levels_button->handle_events(evt);
  if (continue_button) continue_button->handle_events(evt);
  if (restart_button) restart_button->handle_events(evt);
}

void WinPage::update(UpdateData dat) {}

void WinPage::render(RenderData ren) {
  title.render(ren);
  restart_button->render(ren);
  continue_button->render(ren);
  levels_button->render(ren);
  score_text->render(ren);
}
