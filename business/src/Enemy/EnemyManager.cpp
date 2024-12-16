#include "../../include/Enemy/EnemyManager.hpp"
#include <iostream>
#include <list>
#include <memory>
#include <random>

void EnemyManager::assign_tickets(BaseEnemy::EnemyType type, int count) {
  // Remove existing ticket entry for the type, if any
  tickets.remove_if([&](const auto &pair) { return pair.first == type; });
  tickets.emplace_back(type, count);
}
