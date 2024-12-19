#include "WaveManager.hpp"
#include <iostream>

WaveManager::WaveManager(int wave_1_enemies_total, int wave_count)
    : wave(1),
      enemies_total(wave_1_enemies_total),
      enemies_count_on_map(0),
      enemies_killed(0),
      enemies_escaped(0),
      wave_count(wave_count) {}
