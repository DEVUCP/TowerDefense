#pragma once
#include "Enemy/BaseEnemy.hpp"
class EnemyFactory {
public:
  // remove copying
  EnemyFactory(const EnemyFactory&) = delete;
  EnemyFactory& operator=(const EnemyFactory&) = delete;

  /**
   * @brief Get the one instance of EnemyFactory
   */

  void generate_enemy(BaseEnemy::EnemyType);

private:
  EnemyFactory() = default;  //  < private constructor, for singletons

  /*
   * @Brief private functions to ease creation of enemies
   */
  void generate_ant();
  void generate_cockroach();
  void generate_bettle();
};
