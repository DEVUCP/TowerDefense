#include "Pages/PausePage.hpp"
#include <memory>

#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "Game.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

PausePage::PausePage(unsigned width, unsigned height)
    : Page(width, height), title("Pause", width, height) {
  unsigned start_x = width / 2, start_y = height / 2;
  int offset_y = 20;
  int button_spacing_x = 80;

  restart_button = std::make_shared<IconButton>(
      "./assets/buttons/Restart.png", "./assets/buttons/Restart_Hover.png",
      start_x - button_spacing_x, start_y + offset_y);
  restart_button->set_handler([this]() {
    Game::get_instance().init_level(
        Game::get_instance().get_level()->get_level_num());
    notify_observers(Event::GAME_PAGE_SWITCH);
  });
  continue_button = std::make_shared<IconButton>(
      "./assets/buttons/Play.png", "./assets/buttons/Play_Hover.png",
      start_x + button_spacing_x, start_y + offset_y);
  continue_button->set_handler([this]() {
    // Game::get_instance().get_level().un_pause();
    notify_observers(Event::GO_BACK_SWITCH);
  });

  levels_button = std::make_shared<IconButton>(
      "./assets/buttons/Levels.png", "./assets/buttons/Levels_Hover.png",
      width - button_spacing_x, height - button_spacing_x);
  levels_button->set_handler(
      [this]() { notify_observers(Event::LEVEL_PAGE_SWITCH); });
}

void PausePage::on_pause() {}
void PausePage::on_unpause() {
  notify_observers(Event::BG_SHADOW_SWITCH);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::LEVEL_MUSIC);
}

void PausePage::handle_events(EventData evt) {
  restart_button->handle_events(evt);
  levels_button->handle_events(evt);
  continue_button->handle_events(evt);
}

void PausePage::update(UpdateData dat) {}

void PausePage::render(RenderData ren) {
  title.render(ren);
  restart_button->render(ren);
  continue_button->render(ren);
  levels_button->render(ren);
}
