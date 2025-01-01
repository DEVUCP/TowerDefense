#include "WaveManager.hpp"
#include <cassert>

WaveManager::WaveManager(int wave_1_enemies_total, int wave_count)
    : wave(1),
      enemies_total(wave_1_enemies_total),
      enemies_count_on_map(0),
      enemies_spawned(0),
      wave_count(wave_count) {}

bool WaveManager::should_spawn_enemy() const {
  // If there are still enemies left to spawn, return true
  return enemies_spawned < enemies_total;
};

bool WaveManager::wave_over() const {
  // The wave is over when the total number of enemies is equal to the sum of
  // killed and escaped enemies
  return enemies_total == enemies_spawned && enemies_count_on_map == 0;
}

void WaveManager::next_wave() {
  assert(wave_over() &&
         "Cannot proceed to the next wave until the current one is over.");

  if (wave < wave_count) {
    wave++;
    enemies_total = static_cast<int>(enemies_total * DIFFICULTY_FACTORY);
    enemies_count_on_map = 0;
  }
}

int WaveManager::get_wave() const { return wave; }

void WaveManager::spawn_enemy() { enemies_spawned++; }

void WaveManager::set_current_enemies(int value) {
  enemies_count_on_map = value;
}

bool WaveManager::is_last_wave() const { return wave == wave_count; }
