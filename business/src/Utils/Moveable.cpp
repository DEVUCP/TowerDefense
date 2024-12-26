#include "Utils/Moveable.hpp"
#include <sched.h>
#include "GameSettings.hpp"

Moveable::Moveable(float x, float y, float velocity, Vector<float> destination)
    : position(x, y),
      dest_point(destination),
      unit_direction((position - destination).normalize()) {}

void Moveable::move_next() {
  if (is_out_of_board()) on_out_of_board();
  if (has_reached_destination()) on_reach();

  this->position = this->position + unit_direction * this->velocity;
}

bool Moveable::has_reached_destination() const {
  return position == dest_point;
}

void Moveable::update_dest(Vector<float> destination) {
  this->dest_point = destination;
  unit_direction = (this->dest_point - this->position).normalize();
}

bool Moveable::is_out_of_board() {
  Vector<unsigned> size = GameSettings::get_instance().get_size();
  return this->position.x > size.x ||
         this->position.y > size.y;  // < This line uses the fact that unsigned
                                     // is never negative, so need to check
}

const float Moveable::get_rotation() const { return rotation; }

void Moveable::set_velocity(int new_v) { velocity = new_v; }

Vector<float> Moveable::get_position() const { return position; }