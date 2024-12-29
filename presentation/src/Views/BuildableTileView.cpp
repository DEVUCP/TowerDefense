#include "Views/BuildableTileView.hpp"
#include <iostream>
#include <memory>
#include "Game.hpp"
#include "Map/BaseTile.hpp"
#include "Tower/BaseTower.hpp"
#include "Views/TileView.hpp"

std::vector<std::string> BuildableTileView::sheets = {
    "./assets/textures/tiles/Buildables/1.png",
    "./assets/textures/tiles/Buildables/2.png",
    "./assets/textures/tiles/Buildables/3.png",
};
BuildableTileView::BuildableTileView(std::shared_ptr<BaseTile> tile)
    : TileView(tile) {
  load_sheets(sheets);
}

void BuildableTileView::handle_events(EventData data) {
  TileView::handle_events(data);
  if (tower) tower->handle_events(data);
}
void BuildableTileView::render(RenderData ren) {
  TileView::render(ren);
  if (tower) tower->render(ren);
}
void BuildableTileView::update(UpdateData upd) {
  TileView::update(upd);
  if (tower) tower->update(upd);
}

bool BuildableTileView::build_tower(BaseTower::TowerType type) {
  auto lvl = Game::get_instance().get_level();
  auto converted_tile = std::dynamic_pointer_cast<BuildableTile>(tile);
  auto twr = lvl->build_tower(type, converted_tile);
  if (twr) {
    tower = std::make_shared<TowerView>(twr);
    std::cout << "made a tower" << std::endl;
    return true;
  } else {
    std::cout << "you don't have enough coins to buy that tower" << std::endl;
    return false;
  }
  return true;
}
