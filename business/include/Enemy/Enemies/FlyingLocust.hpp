#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class FlyingLocust : public BaseEnemy {
public:
  static constexpr int VELOCITY = 6;
  static constexpr int KILL_COINS = 2;
  static constexpr int INITIAL_HEALTH = 1;

public:
  FlyingLocust(float x, float y, Vector<float> dest);

private:
  virtual void on_killed() override;
};
