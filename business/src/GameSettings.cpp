#include "GameSettings.hpp"

#define SIDEBAR_WIDTH_COLS (5)
#define TILE_LENGTH (60)
#define WIDTH (1920 - TILE_LENGTH * SIDEBAR_WIDTH_COLS)
#define HEIGHT (1080)
#define ROW_NUM (HEIGHT / TILE_LENGTH)
#define COLUMN_NUM (WIDTH / TILE_LENGTH)

GameSettings& GameSettings::get_instance() {
  static GameSettings gs;
  return gs;
}

Vector<unsigned> GameSettings::get_size() const { return {WIDTH, HEIGHT}; }
unsigned GameSettings::get_tile_size() const { return TILE_LENGTH; }
unsigned GameSettings::get_rows() const { return ROW_NUM; }
unsigned GameSettings::get_columns() const { return COLUMN_NUM; }
unsigned GameSettings::get_sidebar_row_count() const {
  return SIDEBAR_WIDTH_COLS;
}
