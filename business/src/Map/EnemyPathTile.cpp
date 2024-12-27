#include "Map/EnemyPathTile.hpp"
#include <algorithm>
#include "Map/BaseTile.hpp"

EnemyPathTile::EnemyPathTile(float x, float y) : BaseTile(x, y, EnemyPath) {}

std::vector<std::shared_ptr<BaseEnemy>> EnemyPathTile::get_enemies() const {
  return enemies;
};

void EnemyPathTile::register_enemy(std::shared_ptr<BaseEnemy> enm) {
  enemies.push_back(enm);
}

void EnemyPathTile::remove_enemy(std::shared_ptr<BaseEnemy> enm) {
  enemies.erase(std::find(enemies.begin(), enemies.end(), enm));
}
