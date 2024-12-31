#include "Enemy/EnemyManager.hpp"
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <stdexcept>
#include "Enemy/EnemyFactory.hpp"

void EnemyManager::assign_tickets(const BaseEnemy::EnemyType &type,
                                  const int &count) {
  // Remove existing ticket entry for the type, if any
  tickets.remove_if([&](const auto &pair) { return pair.first == type; });
  tickets.emplace_back(type, count);
}

int EnemyManager::get_starting_wave(const BaseEnemy::EnemyType &type) const {
  auto it = starting_waves.find(type);
  return (it != starting_waves.end()) ? it->second
                                      : -1;  // Default to -1 if not found
}

void EnemyManager::set_starting_wave(const BaseEnemy::EnemyType &type,
                                     const int &wave) {
  starting_waves[type] = wave;
}

void EnemyManager::process_enemies_states(
    std::function<void(std::shared_ptr<BaseEnemy>)> on_enemy_death,
    std::function<void(std::shared_ptr<BaseEnemy>)> on_enemy_out_of_bound) {
  for (auto itr = enemies.begin(); itr != enemies.end();) {
    switch ((*itr)->get_state()) {
      case BaseEnemy::ENTERING:
        itr++;
        break;
      case BaseEnemy::ON_BOARD:
        itr++;
        break;
      case BaseEnemy::OUT_BOUND:
        on_enemy_out_of_bound(*itr);
        itr = enemies.erase(itr);
        // TODO: Decrease lives
        break;
      case BaseEnemy::DEAD:
        on_enemy_death(*itr);
        itr = enemies.erase(itr);
        break;
    }
  }
}

void EnemyManager::move_enemies() const {
  for (auto &enemy : enemies)
    if (enemy) enemy->move_next();
}

std::shared_ptr<BaseEnemy> EnemyManager::generate_enemy(
    const int &starting_wave) {
  int total_tickets = 0;

  // Calculate total tickets for enemy types considering the wave conditions
  for (const auto &[type, count] : tickets) {
    int enemy_wave = get_starting_wave(type);
    if (enemy_wave <= starting_wave) {
      total_tickets += count;  // Add tickets for this type
    }
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
    int enemy_wave = get_starting_wave(type);
    if (enemy_wave <=
        starting_wave) {  // Only consider types that fit the wave condition
      cumulative += count;
      if (random_ticket <= cumulative) {
        // Get the starting wave for the enemy type
        if (starting_wave == -1) {
          throw std::runtime_error(
              "Starting wave not assigned for the enemy type.");
        }

        // Create and return the corresponding enemy type
        return EnemyFactory::get_intance().generate_enemy(type);
      }
    }
  }

  throw std::logic_error(
      "Failed to generate an enemy. This should not happen.");
}

void EnemyManager::regiseter_enemy(std::shared_ptr<BaseEnemy> enm) {
  enemies.push_back(enm);
}

int EnemyManager::get_enemy_count() const { return enemies.size(); }
