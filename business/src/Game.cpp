#include "Game.hpp"
#include "LevelReader.hpp"

Game& Game::get_instance() {
  static Game game;
  return game;
}

std::shared_ptr<Level> Game::get_level() { return lvl; }

std::shared_ptr<Level> Game::init_level(int level_num) {
  return LevelReader::get_instance().build_level(level_num);
}
