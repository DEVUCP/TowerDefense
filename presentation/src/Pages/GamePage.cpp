#include "Pages/GamePage.hpp"
#include <bits/types/wint_t.h>
#include <memory>
#include "GameSettings.hpp"

GamePage::GamePage(unsigned width, unsigned height) : Page(width, height) {
  init_map();
}

void GamePage::on_pause() {}

void GamePage::on_unpause() {}

void GamePage::handle_events(EventData evt) {
  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->handle_events(evt);
    }
  }
}

void GamePage::render(std::shared_ptr<sf::RenderTarget> window) {
  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->render(window);
    }
  }
}

void GamePage::update() {
  // Here calls Game::get_instance().get_level().run_iteration()
}

void GamePage::init_map() {
  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();
  auto len = GameSettings::get_instance().get_tile_size();

  map.resize(row);
  for (int i = 0; i < row; i++) {
    map[i].resize(col);
    for (int j = 0; j < col; j++) {
      map[i][j] = std::make_shared<TileView>(static_cast<float>(i * len),
                                             static_cast<float>(j * len));
    }
  }
}
