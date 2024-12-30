#include "Utils/Moveable.hpp"
#include <sched.h>
#include <iostream>
#include "GameSettings.hpp"
#include "Utils/Positionable.hpp"
#include "cmath"

Moveable::Moveable(float x, float y, float velocity, Vector<float> destination)
    : Positionable(x, y),
      dest_point{destination},
      unit_direction((destination - get_position()).normalize()),
      velocity(velocity) {
  // std::cout << position.x << " " << position.y << std::endl;
  // std::cout << destination.x << " " << destination.y << std::endl;
}

void Moveable::move_next() {
  if (is_out_of_board()) on_out_of_board();
  if (has_reached_destination()) on_reach();

  update_position(get_position() + unit_direction * velocity);
  on_move();
}

bool Moveable::has_reached_destination() const {
  return get_position().get_distance_to(dest_point) < velocity;
}

void Moveable::update_dest(Vector<float> destination) {
  this->dest_point = destination;
  unit_direction = (this->dest_point - get_position()).normalize();
}

bool Moveable::is_out_of_board() {
  Vector<unsigned> size = GameSettings::get_instance().get_size();
  Vector<float> pos = get_position();
  return pos.x < 0 || pos.x > size.x || pos.y < 0 || pos.y >= size.y;
}

float Moveable::get_rotation() const {
  assert(unit_direction.has_direction());
  return unit_direction.get_angle();
}

void Moveable::set_velocity(int new_v) { velocity = new_v; }
