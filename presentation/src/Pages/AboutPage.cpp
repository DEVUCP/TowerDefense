#include "Pages/AboutPage.hpp"
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Event.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Widgets/MuteButton.hpp"

AboutPage::AboutPage(unsigned width, unsigned height)
    : Page(width, height), title("Who are we?", width, 100) {
  // Initialize the go back button
  go_back =
      std::make_shared<IconButton>("./assets/buttons/GoBack.png",
                                   "./assets/buttons/GoBack_Hover.png", 60, 60);
  go_back->set_handler([this]() { notify_observers(Event::GO_BACK_SWITCH); });

  if(!image_texture.loadFromFile("./assets/textures/team.jpg")) {
    std::cerr << "Failed to load about page image" << std::endl;
    exit(1);
  }

  image.setTexture(image_texture);
  image.setPosition(100, 150);
  image.setScale(
      static_cast<float>(width - 200) / image_texture.getSize().x,
      static_cast<float>(height - 250) / image_texture.getSize().y);

  about_text = std::make_shared<Text>("We made this game as a project for our Data Structures course in uni. HOPE YOU LIKE IT!!", 30, sf::Color::White,width/2, height - 50);
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
  ren.window->draw(image);
}
