#include "WaveManager.hpp"
#include <assert.h>

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

int WaveManager::get_enemies_on_map() const { return enemies_count_on_map; }

bool WaveManager::wave_over() const {
  return enemies_total == enemies_killed + enemies_escaped;
}

void WaveManager::next_wave() {
  assert(wave_over() &&
         "Cannot proceed to the next wave until the current one is over.");

  if (wave < wave_count) {
    wave++;
    enemies_total = static_cast<int>(enemies_total * DIFFICULTY_FACTORY);
    enemies_count_on_map = 0;
    enemies_killed = 0;
    enemies_escaped = 0;
  }
}

int WaveManager::get_wave() const { return wave; }
