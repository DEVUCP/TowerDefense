#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class VoidButterfly : public BaseEnemy {
public:
  static constexpr int VELOCITY = 2;
  static constexpr int KILL_COINS = 20;
  static constexpr int INITIAL_HEALTH = 20;

public:
  VoidButterfly(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
