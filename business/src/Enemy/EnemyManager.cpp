#include "Enemy/EnemyManager.hpp"
#include <iostream>
#include <list>
#include <memory>
#include <random>

void EnemyManager::assign_tickets(BaseEnemy::EnemyType type, int count) {
  // Remove existing ticket entry for the type, if any
  tickets.remove_if([&](const auto &pair) { return pair.first == type; });
  tickets.emplace_back(type, count);
}

std::shared_ptr<BaseEnemy> EnemyManager::generate_enemy() {
  int total_tickets = 0;
  for (const auto &[type, count] : tickets) {
    total_tickets += count;
  }
  if (!total_tickets) {
    throw std::runtime_error("No tickets available to generate an enemy.");
  }

  // Generate a random number in the range [1, total_tickets]
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, total_tickets);
  int random_ticket = dis(gen);

  // Determine which enemy type corresponds to the random ticket
  int cumulative = 0;
  for (const auto &[type, count] : tickets) {
    cumulative += count;
    if (random_ticket <= cumulative) {
      // Get the starting wave for the enemy type
      int wave = get_starting_wave(type);
      if (wave == -1) {
        throw std::runtime_error(
            "Starting wave not assigned for the enemy type.");
      }

      // Create and return the corresponding enemy with wave information
      // Example: return BaseEnemy::create(type, wave);
      // assuming create method takes wave info.
    }
  }

  throw std::logic_error(
      "Failed to generate an enemy. This should not happen.");
}

int EnemyManager::get_starting_wave(BaseEnemy::EnemyType type) const {
  auto it = starting_waves.find(type);
  return (it != starting_waves.end()) ? it->second
                                      : -1;  // Default to -1 if not found
}

void EnemyManager::set_starting_wave(BaseEnemy::EnemyType type, int wave) {
  starting_waves[type] = wave;
}

void EnemyManager::filter_enemies() {
  for (int i = 0; i < enemies.size(); i++) {
    if (enemies[i]->is_to_be_removed()) enemies.erase(enemies.begin() + 1);
  }
}

void EnemyManager::move_enemies() {
  for (auto &enemy : enemies) {
    if (enemy) {
      enemy->move_next();
    }
  }
}
