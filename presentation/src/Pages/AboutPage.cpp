#include "Pages/AboutPage.hpp"
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

AboutPage::AboutPage(unsigned width, unsigned height)
    : Page(width, height), title("About us", width, 100) {
  // Initialize the go back button
  go_back =
      std::make_shared<IconButton>("./assets/buttons/GoBack.png",
                                   "./assets/buttons/GoBack_Hover.png", 60, 60);
  go_back->set_handler([this]() { notify_observers(Event::GO_BACK_SWITCH); });
  mute_button = std::make_shared<MuteButton>(60, height - 60);
}

void AboutPage::on_pause() {}
void AboutPage::on_unpause() {
  notify_observers(Event::BG_DEFAULT_SWITCH);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::MAIN_MUSIC);
  mute_button->check_status();
}

void AboutPage::handle_events(EventData evt) {
  go_back->handle_events(evt);
  mute_button->handle_events(evt);
}

void AboutPage::update(UpdateData dat) { mute_button->check_status(); }

void AboutPage::render(RenderData ren) {
  title.render(ren);
  go_back->render(ren);
  mute_button->render(ren);
}