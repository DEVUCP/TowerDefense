#include "Pages/GamePage.hpp"
#include <algorithm>
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Enums/Event.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Views/BuildableTileView.hpp"
#include "Views/EnemyPathTileView.hpp"
#include "Views/EnemyView.hpp"
#include "Views/NonBuildableTileView.hpp"

GamePage::GamePage(unsigned width, unsigned height) : Page(width, height) {
  init_map();
  init_sidebar();
  // TODO: Remove this temporary test for EnemyView
  // auto tile_in = Game::get_instance().get_level()->get_map()->get_tile(3, 4);
  // auto enm =
  //     std::make_shared<LeafBug>(tile_in->get_position().x,
  //                               tile_in->get_position().y, Vector<float>(0,
  //                               0));
  // auto enemy_path = std::dynamic_pointer_cast<EnemyPathTile>(tile_in);
  // enemy_path->register_enemy(enm);
  // auto view = std::make_shared<EnemyView>(enm);
  // enemies.push_back(view);

  // Set a callback for the business
  init_callbacks();
}

void GamePage::on_pause() {}

void GamePage::on_unpause() {
  notify_observers(Event::BG_CLEAR);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::LEVEL_MUSIC);
}

void GamePage::handle_events(EventData evt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    // Game::get_instance().get_level().pause();
    notify_observers(Event::PAUSE_PAGE_SWITCH);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    // Game::get_instance().get_level()->end_game();
    notify_observers(Event::WIN_PAGE_REPLACE);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    // Game::get_instance().get_level()->end_game();
    notify_observers(Event::LOSE_PAGE_REPLACE);
  }

  auto row = map.size();
  auto col = map[0].size();
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      map[i][j]->handle_events(evt);
    }
  }

  sidebar->handle_events(evt);
}

void GamePage::render(RenderData ren) {
  for (auto& row : map)
    for (auto tl : row) tl->render(ren);
  for (auto& enm : enemies) enm->render(ren);
  for (auto& attack : attacks) attack->render(ren);
  sidebar->render(ren);
}

void GamePage::update(UpdateData dat) {
  // Iterate in the game
  Game::get_instance().get_level()->run_iteration();
  for (auto& row : map)
    for (auto tl : row) tl->update(dat);

  // Update enemies
  for (auto& enm : enemies) enm->update(dat);
  // Update attacks
  for (auto& att : attacks) att->update(dat);
  // Update sidebar
  sidebar->update(dat);
}

void GamePage::init_map() {
  auto row = GameSettings::get_instance().get_rows();
  auto col = GameSettings::get_instance().get_columns();
  auto len = GameSettings::get_instance().get_tile_size();

  map.resize(row, std::vector<std::shared_ptr<TileView>>(col));
  auto lvl = Game::get_instance().get_level();
  auto mmap = lvl->get_map();
  assert(mmap);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      auto tile = mmap->get_tile(i, j);
      assert(tile != nullptr);

      std::shared_ptr<TileView> view = nullptr;
      auto type = tile->get_type();
      switch (type) {
        case BaseTile::Buildable: {
          auto res = std::make_shared<BuildableTileView>(tile);
          res->set_handler([this, res]() { set_selected(res); });
          view = std::move(res);
          break;
        };
        case BaseTile::NonBuildable:
          view = std::make_shared<NonBuildableTileView>(tile);
          break;
        case BaseTile::EnemyPath:
          view = std::make_shared<EnemyPathTileView>(tile);
          break;
      }
      map[i][j] = std::move(view);
    }
}
void GamePage::init_sidebar() { sidebar = std::make_shared<Sidebar>(); }

void GamePage::set_selected(std::shared_ptr<TileView> tile_view) {
  if (selected_tile != nullptr) selected_tile->set_selected(false);
  selected_tile = tile_view;
  selected_tile->set_selected(true);

  auto tile = std::dynamic_pointer_cast<BuildableTileView>(tile_view);

  sidebar->set_tile_target(tile_view);

  if (tile->get_tower_view() != nullptr) {
    auto tower = tile->get_tower_view()->get_tower();
    sidebar->show_upgrades();
  } else {
    sidebar->hide_upgrades();
  }

}

void GamePage::init_callbacks() {
  auto lvl = Game::get_instance().get_level();
  assert(lvl != nullptr);

  lvl->set_on_enemy_created([this](std::shared_ptr<BaseEnemy> enm) {
    enemies.push_back(std::make_shared<EnemyView>(enm));
  });
  lvl->set_on_attack_created([this](std::shared_ptr<BaseAttack> att) {
    attacks.push_back(std::make_shared<AttackView>(att));
  });
  lvl->set_on_enemy_death([this](std::shared_ptr<BaseEnemy> enm) {
    enemies.erase(std::find_if(enemies.begin(), enemies.end(),
                               [enm](std::shared_ptr<EnemyView> view) {
                                 return view->get_enemy() == enm;
                               }));
  });
  lvl->set_on_enemy_out_of_bound([this](std::shared_ptr<BaseEnemy> enm) {
    enemies.erase(std::find_if(enemies.begin(), enemies.end(),
                               [enm](std::shared_ptr<EnemyView> view) {
                                 return view->get_enemy() == enm;
                               }));
  });
  lvl->set_on_attack_hit([this](std::shared_ptr<BaseAttack> att) {
    // attacks.erase(std::find_if(attacks.begin(), attacks.end(),
    //                            [att](std::shared_ptr<AttackView> view) {
    //                              return view->get_attack() == att;
    //                            }));
    // TODO: ADD SFX HERE
  });
  lvl->set_on_attack_out_of_bound([this](std::shared_ptr<BaseAttack> att) {
    attacks.erase(std::find_if(attacks.begin(), attacks.end(),
                               [att](std::shared_ptr<AttackView> view) {
                                 return view->get_attack() == att;
                               }));
  });
}
