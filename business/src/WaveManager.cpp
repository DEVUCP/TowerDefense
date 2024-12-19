#include "WaveManager.hpp"
#include <iostream>

WaveManager::WaveManager(int wave_1_enemies_total, int wave_count)
    : wave(1),
      enemies_total(wave_1_enemies_total),
      enemies_count_on_map(0),
      enemies_killed(0),
      enemies_escaped(0),
      wave_count(wave_count) {}

bool WaveManager::should_spawn_enemy() const {
  // If there are still enemies left to spawn, return true
  return enemies_count_on_map < enemies_total;
};

int WaveManager::get_total_enemies_spawned() const {
  return enemies_killed + enemies_count_on_map;
}

int WaveManager::get_killed_enemies() const { return enemies_killed; }
