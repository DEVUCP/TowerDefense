#include "Collidable.hpp"

Collidable::Collidable(float x, float y, float width, float height,
                       bool enabled)
    : position(Vector<float>{x, y}),
      size(Vector<float>{width, height}),
      enabled(enabled)

{}

void enable_collision() { this->enabled = true; }

void disable_collision() { this->enabled = false; }

private:
Vector<float> tl() const { return position; }

Vector<float> tr() const {
  return Vector<float>(position.x + width, position.y);
}

Vector<float> bl() const {
  return Vector<float>(position.x, position.y - height);
}

Vector<float> br() const {
  return Vector<float>(position.x + width, position.y - height);
}
