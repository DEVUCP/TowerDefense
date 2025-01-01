#include "GameSettings.hpp"

#define TILE_LENGTH (120)
#define ENEMY_WIDTH (60)
#define ENEMY_HEIGHT (60)
#define SIDEBAR_WIDTH_COLS (3)
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
unsigned GameSettings::get_enemy_width() const { return ENEMY_WIDTH; }
unsigned GameSettings::get_enemy_height() const { return ENEMY_HEIGHT; }
