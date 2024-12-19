#pragma once
#include <Level.hpp>

class LevelReader {
public:
  // remove copying
  LevelReader(const LevelReader&) = delete;
  LevelReader& operator=(const LevelReader&) = delete;

  /**
   * @breif Build a level
   * Read information and plug them into `Level` and assign tickets to the
   * `EnemyManager`
   *
   * @details Levels data are stored in `data` directory
   *
   * @param level_num The level number
   */
  std::shared_ptr<Level> build_level(int);

  /**
   * @breif Get the number of level files in data directory.
   */
  int levels_count();

  /**
   * @brief Get the singleton instance of LevelReader
   */
  static LevelReader& get_instance() {
    static LevelReader instance;
    return instance;
  }

private:
  LevelReader() = default;
};
