#include "App.hpp"
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "SFML/Window/Event.hpp"

App::App() : background_mng("assets/background/Default.png") { init_window(); }

void App::init_window() {
  window = std::make_unique<sf::RenderWindow>(
      sf::VideoMode::getFullscreenModes()[0], "SFML", sf::Style::Fullscreen);
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
      // TODO: handle elsewhere
    }
  }
}

void App::update() {
  // update the game
}

void App::render() {
  window->clear();

  // render stuff

  window->display();
}
