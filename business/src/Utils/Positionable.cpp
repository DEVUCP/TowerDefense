#include "Utils/Positionable.hpp"

Positionable::Positionable(float x, float y) : position{x, y} {}
Vector<float> Positionable::get_position() const { return position; }
void Positionable::update_position(Vector<float> new_position) {
  position = new_position;
}
