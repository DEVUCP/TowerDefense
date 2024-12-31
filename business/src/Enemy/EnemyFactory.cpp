#include <Enemy/EnemyFactory.hpp>
#include <iostream>
#include <stdexcept>
#include "Enemy/BaseEnemy.hpp"
#include "Enemy/Enemies/ClampBeetle.hpp"
#include "Enemy/Enemies/LeafBug.hpp"
#include "Enemy/Enemies/MagmaCrab.hpp"
#include "Game.hpp"

EnemyFactory& EnemyFactory::get_intance() {
  static EnemyFactory fac;
  return fac;
}

std::shared_ptr<BaseEnemy> EnemyFactory::generate_enemy(
    BaseEnemy::EnemyType type) {
  auto lvl = Game::get_instance().get_level();
  auto map = lvl->get_map();
  auto starting_pos_enemies = map->get_initial_enemy_position();
  auto starting_dest_enemy = map->get_initial_enemy_destination();

  std::cout << starting_pos_enemies.x << " " << starting_pos_enemies.y
            << std::endl;
  switch (type) {
    case BaseEnemy::EnemyType::LEAF_BUG:
      return std::make_shared<LeafBug>(
          starting_pos_enemies.x, starting_pos_enemies.y, starting_dest_enemy);
    case BaseEnemy::EnemyType::MAGMA_CRAB:
      return std::make_shared<MagmaCrab>(
          starting_pos_enemies.x, starting_pos_enemies.y, starting_dest_enemy);
    case BaseEnemy::EnemyType::CLAMP_BEETLE:
      return std::make_shared<ClampBeetle>(
          starting_pos_enemies.x, starting_pos_enemies.y, starting_dest_enemy);
    default:
      throw std::runtime_error("No constructor provided for all enemy types");
  }
}
