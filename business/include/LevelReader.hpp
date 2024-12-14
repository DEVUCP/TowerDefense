#pragma once

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
  void build_level(int);

private:
  LevelReader() = default;
};
