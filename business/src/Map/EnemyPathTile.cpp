#include "Map/EnemyPathTile.hpp"
#include "Map/BaseTile.hpp"

EnemyPathTile::EnemyPathTile(float x, float y) : BaseTile(x, y, EnemyPath) {}

std::vector<std::shared_ptr<BaseEnemy>> EnemyPathTile::get_enemies() const {
  return enemies;
};
