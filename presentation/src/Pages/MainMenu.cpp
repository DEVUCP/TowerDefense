#include "Pages/MainMenu.hpp"
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

MainMenu::MainMenu(unsigned width, unsigned height)
    : Page(width, height), title("Bug Slayer", width, height) {
  play_btn = std::make_shared<TextButton>("play", width / 2.f, height / 2.f,
                                          StandardButton::ButtonSize::LARGE,
                                          StandardButton::ButtonType::RECT);
  play_btn->set_handler(
      [this]() { notify_observers(Event::LEVEL_PAGE_SWITCH); });
  about_btn = std::make_shared<TextButton>(
      "about", width / 2.f, height / 2.f + 200,
      StandardButton::ButtonSize::LARGE, StandardButton::ButtonType::RECT);
  about_btn->set_handler(
      [this]() { notify_observers(Event::ABOUT_PAGE_SWITCH); });
  mute_button = std::make_shared<MuteButton>(60, height - 60);
}

void MainMenu::on_pause() {}
void MainMenu::on_unpause() {
  notify_observers(Event::BG_DEFAULT_SWITCH);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::MAIN_MUSIC);
}

void MainMenu::handle_events(EventData evt) {
  play_btn->handle_events(evt);
  about_btn->handle_events(evt);
  mute_button->handle_events(evt);
}

void MainMenu::update(UpdateData dat) { mute_button->check_status(); }

void MainMenu::render(RenderData ren) {
  title.render(ren);
  play_btn->render(ren);
  about_btn->render(ren);
  mute_button->render(ren);
}
