#include "Views/EnemyPathTileView.hpp"
#include <memory>
#include "Map/BaseTile.hpp"
#include "Views/TileView.hpp"

std::vector<std::string> EnemyPathTileView::sheets = {
    "./assets/textures/tiles/Enemypath/1.png",
    "./assets/textures/tiles/Enemypath/2.png",
    "./assets/textures/tiles/Enemypath/3.png",
};
EnemyPathTileView::EnemyPathTileView(std::shared_ptr<BaseTile> tile)
    : TileView(tile) {
  load_sheets(sheets);
}
