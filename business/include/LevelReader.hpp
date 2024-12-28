#pragma once

#include <Level.hpp>

class LevelReader {
public:
  static const inline std::string levels_path = "/data/levels/";

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
   * @breif Generate the file path for the given level number.
   *
   * @param level_num The level number. If level_num is -1, returns the path of
   * the levels directory.
   */
  std::string get_level_path(int);

  /**
   * @brief Get the singleton instance of LevelReader
   */
  static LevelReader& get_instance();

private:
  LevelReader() = default;
};
