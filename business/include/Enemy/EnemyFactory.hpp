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
  static EnemyFactory& get_intance();

  /**
   * @brief Generate an enemy with specifc type
   *
   * @details use private helpers
   */
  std::shared_ptr<BaseEnemy> generate_enemy(BaseEnemy::EnemyType);

private:
  EnemyFactory() = default;
};
