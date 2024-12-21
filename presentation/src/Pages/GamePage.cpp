#include "Pages/GamePage.hpp"
#include <bits/types/wint_t.h>
#include <iostream>
#include <memory>
#include "Enums/Event.hpp"
#include "GameSettings.hpp"
#include "SFML/System/Vector2.hpp"

GamePage::GamePage(unsigned width, unsigned height) : Page(width, height) {
  init_map();
  init_sidebar();
}

void GamePage::on_pause() {}

void GamePage::on_unpause() { notify_observers(Event::BG_CLEAR); }

void GamePage::handle_events(EventData evt) {
  auto row = map.size();
  auto col = map[0].size();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->handle_events(evt);
    }
  }
}

void GamePage::render(std::shared_ptr<sf::RenderTarget> window) {
  auto row = map.size();
  auto col = map[0].size();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->render(window);
    }
  }
  window->draw(sidebar);
}

void GamePage::update() {
  // Here calls Game::get_instance().get_level().run_iteration()
}

void GamePage::init_map() {
  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();
  auto len = GameSettings::get_instance().get_tile_size();

  map.resize(col);
  for (int i = 0; i < col; i++) {
    map[i].resize(row);
    for (int j = 0; j < row; j++) {
      map[i][j] = std::make_shared<TileView>(static_cast<float>(i) * len,
                                             static_cast<float>(j) * len);
    }
  }
}

void GamePage::init_sidebar() {
  auto tile_len = GameSettings::get_instance().get_tile_size();
  auto col = GameSettings::get_instance().get_columns();
  auto h = GameSettings::get_instance().get_size().y;
  auto sidebar_len = GameSettings::get_instance().get_sidebar_row_count();
  sidebar.setPosition(col * tile_len, 0);
  sidebar.setSize(sf::Vector2f(col * tile_len, h));
  sidebar.setFillColor(sf::Color(109, 70, 33));
}
