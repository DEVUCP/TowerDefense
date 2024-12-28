#pragma once

#include "Utils/Vector.hpp"
class Positionable {
public:
  Positionable(float x, float y);

  Vector<float> get_position() const;
  void update_position(Vector<float> new_position);

private:
  Vector<float> position;
};
