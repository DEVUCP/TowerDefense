#include "Pages/MainMenu.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include "Components/BackgroundManager.hpp"
#include "Components/TextButton.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"
#include "Widgets/MainMenu/Title.hpp"

MainMenu::MainMenu(unsigned width, unsigned height)
    : Page(width, height), title(width, height) {
  background.load_img("./assets/background/Default.png", target_width,
                      target_height);
  play_btn = std::make_shared<TextButton>("PLAY", width / 2.f, height / 2.f,
                                          Button::ButtonSize::LARGE,
                                          Button::ButtonType::RECT);
  play_btn->set_handler([]() { std::cout << "clicked" << std::endl; });
}

void MainMenu::on_pause() {}
void MainMenu::on_unpause() {}

void MainMenu::handle_events(EventData evt) {
  // TODO: Change the interface of handle_events to some struct EventData that
  // will be passed down, so I don't get such a problem again
  play_btn->handle_events(evt);
}

void MainMenu::update() {}

void MainMenu::render(std::shared_ptr<sf::RenderTarget> window) {
  background.render(window);
  title.render(window);
  play_btn->render(window);
}
