#pragma once
#include <string>
#include <vector>
#include "Map/BuildableTile.hpp"
#include "Views/TileView.hpp"
#include "Views/TowerView.hpp"

class EnemyPathTileView : public TileView {
public:
  EnemyPathTileView(std::shared_ptr<BaseTile> tile);

private:
  static std::vector<std::string> sheets;
};
