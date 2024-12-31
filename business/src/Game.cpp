#include "Game.hpp"
#include <iostream>
#include "LevelReader.hpp"

Game& Game::get_instance() {
  static Game game;
  return game;
}

std::shared_ptr<Level> Game::get_level() { return lvl; }

void Game::init_level(int level_num) {
  lvl = LevelReader::get_instance().build_level(level_num);
}
