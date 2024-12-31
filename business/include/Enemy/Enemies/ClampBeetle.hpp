#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class ClampBeetle : public BaseEnemy {
public:
  static constexpr int VELOCITY = 4;
  static constexpr int KILL_COINS = 22;
  static constexpr int INITIAL_HEALTH = 15;

public:
  ClampBeetle(float x, float y, Vector<float> dest);

private:
  virtual void on_killed() override;
};
