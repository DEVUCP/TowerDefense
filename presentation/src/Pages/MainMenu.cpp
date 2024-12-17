#include "Pages/MainMenu.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include "Components/BackgroundManager.hpp"
#include "Components/IconButton.hpp"
#include "Components/TextButton.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"
#include "Widgets/MainMenu/Title.hpp"

MainMenu::MainMenu(unsigned width, unsigned height)
    : Page(width, height), title(width, height) {
  background.load_img("./assets/background/Default.png", target_width,
                      target_height);
  play_btn = std::make_shared<TextButton>("play", width / 2.f, height / 2.f,
                                          Button::ButtonSize::LARGE,
                                          Button::ButtonType::RECT);
  play_btn->set_handler([]() { std::cout << "play" << std::endl; });
  // TODO: Make a solution instead of hardcoding the value 200
  about_btn = std::make_shared<TextButton>(
      "about", width / 2.f, height / 2.f + 200, Button::ButtonSize::LARGE,
      Button::ButtonType::RECT);
  about_btn->set_handler([]() { std::cout << "about" << std::endl; });
  mute_button = std::make_shared<IconButton>(
      "./assets/buttons/SoundOn.png", "./assets/buttons/SoundOn_Hover.png", 60,
      height - 60, Button::ButtonSize::DEFAULT, Button::ButtonType::SQUARE);
}

void MainMenu::on_pause() {}
void MainMenu::on_unpause() {}

void MainMenu::handle_events(EventData evt) {
  play_btn->handle_events(evt);
  about_btn->handle_events(evt);
  mute_button->handle_events(evt);
}

void MainMenu::update() {}

void MainMenu::render(std::shared_ptr<sf::RenderTarget> window) {
  background.render(window);
  title.render(window);
  play_btn->render(window);
  about_btn->render(window);
  mute_button->render(window);
}
