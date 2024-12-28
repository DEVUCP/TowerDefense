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

  about_text = std::make_shared<Text>("This game was made as a project for our Data Structures course in uni. WE HOPE YOU LIKE IT!!", 30, sf::Color::White,width/2, height - 50);
}

void AboutPage::on_pause() {}
void AboutPage::on_unpause() {
  notify_observers(Event::BG_DEFAULT_SWITCH);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::MAIN_MUSIC);
}

void AboutPage::handle_events(EventData evt) {
  go_back->handle_events(evt);
}

void AboutPage::update(UpdateData dat) {  }

void AboutPage::render(RenderData ren) {
  title.render(ren);
  go_back->render(ren);
  about_text->render(ren);
}
