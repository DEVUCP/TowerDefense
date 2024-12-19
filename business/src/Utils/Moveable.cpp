
#include "Moveable.hpp"

Moveable::Moveable(float x, float y, float velocity,
                   Vector<float> destination) {
  this->position = Vector<float>(x, y);
  this->velcoity = velocity;
  this->dest_point = destination;
}

void Moveable::move_next() {
  if (is_out_of_board()) on_out_of_board();
  if (is_reached_destination()) on_reach();

  this->position += unit_direction * this->velcoity;
}

bool is_reached_destination() { return this->position == this->dest_point; }

void Moveable::update_dest(Vector<float> destination) {
  this->dest_point = destination;
  unit_direction = this->dest_point - this->position;
}

bool Moveable::is_out_of_board() {
  return this->position.x > GameSettings.WIDTH ||
         this->position.y GameSettings.HEIGHT
}

const float get_rotation() const { return rotation; }