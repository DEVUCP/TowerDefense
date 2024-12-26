#include "Views/NonBuildableTileView.hpp"
#include <memory>
#include "Map/BaseTile.hpp"
#include "Views/TileView.hpp"

std::vector<std::string> NonBuildableTileView::sheets = {
    "./assets/textures/tiles/Nonbuildables/1.png",
    "./assets/textures/tiles/Nonbuildables/2.png",
    "./assets/textures/tiles/Nonbuildables/3.png",
};
NonBuildableTileView::NonBuildableTileView(std::shared_ptr<BaseTile> tile)
    : TileView(tile) {
  load_sheets(sheets);
}
