#include "Game.hpp"

Game& Game::get_instance() {
  static Game game;
  return game;
}

std::shared_ptr<Level> Game::get_level() { return lvl; }
