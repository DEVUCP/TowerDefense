
#include "Map/BaseTile.hpp"
#include "GameSettings.hpp"


BaseTile::BaseTile(float x, float y, TileType type)
    : Drawable("", Vector<float>(0, 0)),position(Vector<float>(x, y)), type(type) {}

Vector<float> BaseTile::get_center() const {
  unsigned tile_size = GameSettings::get_instance().get_tile_size();
  return Vector<float>(tile_size / 2.0, tile_size / 2.0);
}

Vector<float> BaseTile::get_position() const {
  return position;
}
