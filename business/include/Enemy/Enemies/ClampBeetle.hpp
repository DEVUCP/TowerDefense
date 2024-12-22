#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class ClampBeetle : public BaseEnemy {
public:
  static constexpr int velocity = 10;
  static constexpr int kill_coins = 5;
  static constexpr int initial_health = 10;

public:
  ClampBeetle(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
