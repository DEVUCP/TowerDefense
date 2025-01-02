#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class Scorpion : public BaseEnemy {
public:
  static constexpr int VELOCITY = 4;
  static constexpr int KILL_COINS = 4;
  static constexpr int INITIAL_HEALTH = 12;

public:
  Scorpion(float x, float y, Vector<float> dest);

private:
  virtual void on_killed() override;
};
