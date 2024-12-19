
#include "BaseTile.cpp"

public:
BaseTile(float x, float y, TileType type)
    : position(Vector<float>(x, y)), type(type) {}

Vector<float> get_center() const {
  int tile_size = GameSettings::get_instance().get_tile_size();
  return Vector<float>(tile_size / 2, tile_size / 2)
}
