#include "Utils/Collidable.hpp"
#include "Utils/Positionable.hpp"

Collidable::Collidable(float x, float y, float width, float height,
                       bool enabled)
    : Positionable(x, y),
      size(Vector<float>{width, height}),
      enabled(enabled) {}

bool Collidable::collide_with(const Collidable& other) {
  auto position = get_position();
  auto other_position = other.get_position();

  return !(position.x + size.x < other_position.x ||  // this right < other left
           position.x >
               other_position.x + other.size.x ||     // this left > other right
           position.y + size.y < other_position.y ||  // this bottom < other top
           position.y >
               other_position.y + other.size.y);  // this top > other bottom
}

bool Collidable::point_colliding(Vector<float> point) {
  auto position = get_position();
  return (point.x >= position.x && point.x <= position.x + size.x) &&
         (point.y >= position.y && point.y <= position.y + size.y);
}

void Collidable::enable_collision() { this->enabled = true; }

void Collidable::disable_collision() { this->enabled = false; }

Vector<float> Collidable::tl() const { return get_position(); }

Vector<float> Collidable::tr() const {
  auto position = get_position();
  return Vector<float>(position.x + size.x, position.y);
}

Vector<float> Collidable::bl() const {
  auto position = get_position();
  return Vector<float>(position.x, position.y + size.y);
}

Vector<float> Collidable::br() const {
  auto position = get_position();
  return Vector<float>(position.x + size.x, position.y + size.y);
}
