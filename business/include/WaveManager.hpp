#pragma once

#define DIFFICULTY_FACTORY 1.5

class WaveManager {
public:
  /**
   * @brief Constructor
   */
  WaveManager(int wave_1_enemies_total, int wave_count);

  /**
   * @brief Check if there are enemies to spawn
   */
  bool should_spawn_enemy() const;

  /**
   * @brief decrease the number of enemies on the map
   */
  void spawn_enemy();

  /**
   * @brief Set the number of enemies on the map
   */
  void set_current_enemies(int value);

  /**
   * @brief Returns the amount of enemies killed
   */
  int get_killed_enemies() const;

  /**
   * @brief Check if the wave is over or not
   *
   * @details A wave is done when `enemies_total` = `enemies_killed` +
   * `enemies_escaped`
   */
  bool wave_over() const;

  /**
   * @brief Proceed to next wave
   *
   * @detials, In each wave, the number of enemies = DIFFICULTY_FACTORY *
   * previous wave. Initial number is given in Constructor
   * @detail Must assert that current wave is over
   */
  void next_wave();

  /**
   * @brief Get the current wave
   */
  int get_wave() const;

private:
  int wave;
  int enemies_total;  // all enemies count in the current wave, either sent or
                      // not
  int enemies_count_on_map;  // all enemies that are in the current wave, but
                             // haven't been killed
  int enemies_spawned;       // Total enemies removed already
  int wave_count;            // number of waves in the current level
};
