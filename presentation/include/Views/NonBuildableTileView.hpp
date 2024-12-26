#pragma once
#include <string>
#include <vector>
#include "Map/BuildableTile.hpp"
#include "Views/TileView.hpp"
#include "Views/TowerView.hpp"

class NonBuildableTileView : public TileView {
public:
  NonBuildableTileView(std::shared_ptr<BaseTile> tile);

private:
  static std::vector<std::string> sheets;
};
