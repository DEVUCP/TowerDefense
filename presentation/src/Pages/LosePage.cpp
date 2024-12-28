#include "Pages/LosePage.hpp"
#include <memory>

#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "Game.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

LosePage::LosePage(unsigned width, unsigned height)
    : Page(width, height), title("Game Over", width, height) {

  unsigned start_x = width/2, start_y = height/2;
  int offset_y = 20;
  int buttons_spacing_x = 80;

  restart_button =
      std::make_shared<IconButton>("./assets/buttons/Restart.png",
                                   "./assets/buttons/Restart_Hover.png", start_x - buttons_spacing_x, start_y + offset_y);
  restart_button->set_handler([this]() {
    Game::get_instance().init_level(Game::get_instance().get_level()->get_level_num());
    notify_observers(Event::GAME_PAGE_SWITCH);
  });
  levels_button =
      std::make_shared<IconButton>("./assets/buttons/Levels.png",
                                   "./assets/buttons/Levels_Hover.png", start_x + buttons_spacing_x, start_y + offset_y);
  levels_button->set_handler([this]() { notify_observers(Event::LEVEL_PAGE_SWITCH); });
}

void LosePage::on_pause() {}
void LosePage::on_unpause() {
  notify_observers(Event::BG_SHADOW_SWITCH);
  // TODO: Change to lose music
  MusicPlayer::get_instance().set_current_music(MusicPlayer::LEVEL_MUSIC);
}

void LosePage::handle_events(EventData evt) {
  restart_button->handle_events(evt);
  levels_button->handle_events(evt);
}

void LosePage::update(UpdateData dat) { }

void LosePage::render(RenderData ren) {
  title.render(ren);
  restart_button->render(ren);
  levels_button->render(ren);
}
