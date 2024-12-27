#include "Pages/WinPage.hpp"
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

WinPage::WinPage(unsigned width, unsigned height)
    : Page(width, height), title("You won!!", width, height) {
  // Initialize the go back button
  go_back =
      std::make_shared<IconButton>("./assets/buttons/GoBack.png",
                                   "./assets/buttons/GoBack_Hover.png", 60, 60);
  go_back->set_handler([this]() { notify_observers(Event::GO_BACK_SWITCH); });
  mute_button = std::make_shared<MuteButton>(60, height - 60);
}

void WinPage::on_pause() {}
void WinPage::on_unpause() {
  notify_observers(Event::BG_SHADOW_SWITCH);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::LEVEL_MUSIC);
  mute_button->check_status();
}

void WinPage::handle_events(EventData evt) {
  go_back->handle_events(evt);
  mute_button->handle_events(evt);
}

void WinPage::update(UpdateData dat) { mute_button->check_status(); }

void WinPage::render(RenderData ren) {
  title.render(ren);
  go_back->render(ren);
  mute_button->render(ren);
}