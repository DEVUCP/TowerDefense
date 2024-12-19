#include "GameSettings.hpp"
#define WIDTH 1680
#define HEIGHT 1080
#define TILE_LENGTH 60
#define ROW_NUM 18
#define COLUMN_NUM 28

GameSettings& GameSettings::get_instance() {
  static GameSettings gs;
  return gs;
}

Vector<unsigned> GameSettings::get_size() { return {WIDTH, HEIGHT}; }
unsigned GameSettings::get_tile_size() { return TILE_LENGTH; }
unsigned GameSettings::get_rows() { return ROW_NUM; }
unsigned GameSettings::get_columns() { return COLUMN_NUM; }