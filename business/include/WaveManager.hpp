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
   * @brief Returns the totunt of eemies that are either in board or killed
   */
  int get_total_enemies_spawned() const;

  /**
   * @brief Returns the amount of enemies killed
   */
  int get_killed_enemies() const;

  /**
   * @brief Returns the number of enemies on map
   */
  int get_enemies_on_map() const;

  /**
   * @brief Check if the wave is over or not
   *
   * @details A wave is done when `enemeis_total` = `enemies_killed` +
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

private:
  int wave;
  int enemies_total;  // all enemies count in the current wave, either sent or
                      // not
  int enemies_count_on_map;  // all enemeis that are in the current wave, but
                             // havn't been killed
  int enemies_killed;        // all killed enemies
  int enemies_escaped;  // all enemeis that traversed the entire map and invoked
                        // damage
  int wave_count;       // number of waves in the current level
};
