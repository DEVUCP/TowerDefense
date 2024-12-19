#include <Enemy/EnemyFactory.hpp>
#include "Enemy/BaseEnemy.hpp"

EnemyFactory& EnemyFactory::get_intance() {
  static EnemyFactory fac;
  return fac;
}

std::shared_ptr<BaseEnemy> EnemyFactory::generate_enemy(
    BaseEnemy::EnemyType type) {
  switch (type) {
    case BaseEnemy::EnemyType::ANT:
      return generate_ant();
    case BaseEnemy::EnemyType::COCKROACH:
      return generate_cockroach();
    case BaseEnemy::EnemyType::BETTLE:
      return generate_bettle();
  }
}

std::shared_ptr<BaseEnemy> EnemyFactory::generate_ant() { return nullptr; }
std::shared_ptr<BaseEnemy> EnemyFactory::generate_cockroach() {
  return nullptr;
}
std::shared_ptr<BaseEnemy> EnemyFactory::generate_bettle() { return nullptr; }
