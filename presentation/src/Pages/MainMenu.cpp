#include "Pages/MainMenu.hpp"
#include <memory>
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
  about_btn->set_handler([]() {});
  mute_button = std::make_shared<MuteButton>(60, height - 60);
}

void MainMenu::on_pause() {}
void MainMenu::on_unpause() {
  mute_button->check_status();
  notify_observers(Event::BG_DEFAULT_SWITCH);
}

void MainMenu::handle_events(EventData evt) {
  play_btn->handle_events(evt);
  about_btn->handle_events(evt);
  mute_button->handle_events(evt);
}

void MainMenu::update() {}

void MainMenu::render(std::shared_ptr<sf::RenderTarget> window) {
  title.render(window);
  play_btn->render(window);
  about_btn->render(window);
  mute_button->render(window);
}
