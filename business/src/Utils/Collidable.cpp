#include "Collidable.hpp"

Collidable::Collidable(float x, float y, float width, float height,
                       bool enabled)
    : position(Vector<float>{x, y}),
      size(Vector<float>{width, height}),
      enabled(enabled)

{}
