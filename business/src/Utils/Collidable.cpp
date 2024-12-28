#include "Utils/Collidable.hpp"
#include "Utils/Positionable.hpp"

Collidable::Collidable(float x, float y, float width, float height,
                       bool enabled)
    : Positionable(x, y),
      size(Vector<float>{width, height}),
      enabled(enabled) {}

bool Collidable::collide_with(const Collidable& other) {
  return point_colliding(other.tl()) && point_colliding(other.tr()) &&
         point_colliding(other.bl()) && point_colliding(other.br());
}

bool Collidable::point_colliding(Vector<float> point) {
  auto position = get_position();
  return (point.x >= position.x && point.x <= position.x + width) &&
         (point.y >= position.y && point.y <= position.y - height);
}

void Collidable::enable_collision() { this->enabled = true; }

void Collidable::disable_collision() { this->enabled = false; }

Vector<float> Collidable::tl() const { return get_position(); }

Vector<float> Collidable::tr() const {
  auto position = get_position();
  return Vector<float>(position.x + width, position.y);
}

Vector<float> Collidable::bl() const {
  auto position = get_position();
  return Vector<float>(position.x, position.y - height);
}

Vector<float> Collidable::br() const {
  auto position = get_position();
  return Vector<float>(position.x + width, position.y - height);
}
