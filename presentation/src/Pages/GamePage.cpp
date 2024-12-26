#include "Pages/GamePage.hpp"
#include <memory>
#include "Components/MusicPlayer.hpp"
#include "Components/SFXPlayer.hpp"
#include "Enemy/Enemies/LeafBug.hpp"
#include "Enums/Event.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
#include "Tower/BaseTower.hpp"
#include "Utils/Vector.hpp"
#include "Views/BuildableTileView.hpp"
#include "Views/EnemyPathTileView.hpp"
#include "Views/EnemyView.hpp"
#include "Views/NonBuildableTileView.hpp"

GamePage::GamePage(unsigned width, unsigned height) : Page(width, height) {
  init_map();
  init_sidebar();
  // TODO: Remove this temporary test for EnemyView
  auto enm = std::make_shared<LeafBug>(500, 500, Vector<float>(600, 600));
  auto view = std::make_shared<EnemyView>(enm);
  enemies.push_back(view);
}

void GamePage::on_pause() {}

void GamePage::on_unpause() {
  notify_observers(Event::BG_CLEAR);
  MusicPlayer::get_instance().set_current_music(MusicPlayer::LEVEL_MUSIC);
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

void GamePage::render(RenderData ren) {
  for (auto& row : map) {
    for (auto tl : row) {
      tl->render(ren);
    }
  }
  for (auto& enm : enemies) enm->render(ren);
  sidebar->render(ren);
}

void GamePage::update(UpdateData dat) {
  // Here calls Game::get_instance().get_level().run_iteration()
  sidebar->update(dat);
  for (auto& enm : enemies) enm->update(dat);
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

void GamePage::set_selected(std::shared_ptr<BuildableTileView> tile_view) {
  selected_tile = tile_view;

  // TODO: This logic is to be transfered to another method, just because
  // business isn't complete
  tile_view->build_tower(BaseTower::IonPrism, tile_view->get_tile());
  SFXPlayer::get_instance().play(SFXPlayer::TOWER_BUILD);
}

void GamePage::build_tower(float i, float j, BaseTower::TowerType) {}
