#include "Pages/GamePage.hpp"
#include <bits/types/wint_t.h>
#include <iostream>
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Enums/Event.hpp"
#include "GameSettings.hpp"
#include "Map/BuildableTile.hpp"
#include "Map/EnemyPathTile.hpp"
#include "Map/NonBuildableTile.hpp"
#include "SFML/System/Vector2.hpp"

GamePage::GamePage(unsigned width, unsigned height) : Page(width, height) {
  init_map();
  init_sidebar();
}

void GamePage::on_pause() {}

void GamePage::on_unpause() {
  notify_observers(Event::BG_CLEAR);
  MusicPlayer::get_instance().play(MusicPlayer::LEVEL_MUSIC);
}

void GamePage::handle_events(EventData evt) {
  auto row = map.size();
  auto col = map[0].size();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->handle_events(evt);
    }
  }
  sidebar->handle_events(evt);
}

void GamePage::render(std::shared_ptr<sf::RenderTarget> window) {
  auto row = map.size();
  auto col = map[0].size();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->render(window);
    }
  }
  sidebar->render(window);
}

void GamePage::update() {
  // Here calls Game::get_instance().get_level().run_iteration()
  sidebar->update();
}

// void GamePage::init_map() {
//   auto row = GameSettings::get_instance().get_rows();
//   auto col = GameSettings::get_instance().get_columns();
//   auto len = GameSettings::get_instance().get_tile_size();
//
//   map.resize(col);
//   for (int i = 0; i < col; i++) {
//     map[i].resize(row);
//     for (int j = 0; j < row; j++) {
//       // TODO: When linking backend to frontend, use get_tile instead of this
//       std::shared_ptr<BaseTile> tile = std::make_shared<NonBuildableTile>(
//           static_cast<float>(i) * len, static_cast<float>(j) * len);
//       map[i][j] = std::make_shared<TileView>(tile);
//     }
//   }
// }

#include <memory>  // For std::shared_ptr
#include <random>  // For random number generation

void GamePage::init_map() {
  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();
  auto len = GameSettings::get_instance().get_tile_size();

  map.resize(col);

  // Random number generation setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 2);  // Randomly choose 0, 1, or 2

  for (int i = 0; i < col; i++) {
    map[i].resize(row);
    for (int j = 0; j < row; j++) {
      // Randomly select tile type
      int tile_type = dis(gen);

      std::shared_ptr<BaseTile> tile;
      if (tile_type == 0) {
        // NonBuildableTile
        tile = std::make_shared<NonBuildableTile>(static_cast<float>(i) * len,
                                                  static_cast<float>(j) * len);
      } else if (tile_type == 1) {
        // BuildableTile
        tile = std::make_shared<BuildableTile>(static_cast<float>(i) * len,
                                               static_cast<float>(j) * len);
      } else {
        // EnemyPathTile
        tile = std::make_shared<EnemyPathTile>(static_cast<float>(i) * len,
                                               static_cast<float>(j) * len);
      }

      map[i][j] = std::make_shared<TileView>(tile);
    }
  }
}
void GamePage::init_sidebar() { sidebar = std::make_shared<Sidebar>(); }
