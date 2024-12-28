#include "Map/BaseTile.hpp"
#include "GameSettings.hpp"
#include "Map/BaseTile.hpp"

BaseTile::BaseTile(float x, float y, TileType type)
    : position(Vector<float>(x, y)), type(type) {}

Vector<float> BaseTile::get_center() const {
  unsigned tile_size = GameSettings::get_instance().get_tile_size();
  return Vector<float>(position.x + tile_size / 2.f,
                       position.y + tile_size / 2.f);
}

BaseTile::TileType BaseTile::get_type() const { return type; }
Vector<float> BaseTile::get_position() const { return position; }
