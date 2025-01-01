#include "App.hpp"
#include <cassert>
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/PageManager.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Views/AttackView.hpp"
#include "Views/EnemyView.hpp"
#include "Views/TowerView.hpp"

App::App() {
  // WARN: this order matters
  init_info();
  init_window();
  init_time();
  init_page_manager();
  MusicPlayer::get_instance()
      .play();  // TODO: Use some local file to update status
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
    deltaTime = clock.restart();
  }
}

void App::handle_events() {
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      window->close();
    } else {
      page_mng->handle_events({event, sf::Mouse::getPosition()});
    }
  }
}

void App::update() { page_mng->update({}); }

void App::render() {
  window->clear();

  page_mng->render({deltaTime, window});

  window->display();
}

void App::init_time() { deltaTime = sf::Time::Zero; }
void App::init_info() {
  TowerView::load_tower_info();
  EnemyView::load_enemy_info();
  AttackView::load_attack_info();
}
