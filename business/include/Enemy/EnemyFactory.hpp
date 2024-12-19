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
  static EnemyFactory get_intance();

  /**
   * @brief Generate an enemy with specifc type
   *
   * @details use private helpers
   */
  std::shared_ptr<BaseEnemy> generate_enemy(BaseEnemy::EnemyType);

private:
  EnemyFactory() = default;  //  < private constructor, for singletons

  /*
   * @Brief private functions to ease creation of enemies
   */
  std::shared_ptr<BaseEnemy> generate_ant();
  std::shared_ptr<BaseEnemy> generate_cockroach();
  std::shared_ptr<BaseEnemy> generate_bettle();
};
