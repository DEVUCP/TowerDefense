#include "App.hpp"
#include <cassert>
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/PageManager.hpp"
#include "SFML/Window/Event.hpp"

App::App() {
  init_window();
  init_page_manager();
  MusicPlayer::get_instance().play(MusicPlayer::MAIN_MUSIC);
}

void App::init_window() {
  window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode::getFullscreenModes()[0], "SFML", sf::Style::Fullscreen);
}

void App::init_page_manager() {
  assert(window);  // assert the initialization of window
  page_mng =
      std::make_shared<PageManager>(window->getSize().x, window->getSize().y);
  page_mng->go_to_page(PageType::MAIN_MENU);
}
void App::run() {
  while (window->isOpen()) {
    handle_events();
    update();
    render();
  }
}

void App::handle_events() {
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    } else {
      page_mng->handle_events({event, sf::Mouse::getPosition()});
    }
  }
}

void App::update() { page_mng->update(); }

void App::render() {
  window->clear();

  page_mng->render(window);

  window->display();
}
