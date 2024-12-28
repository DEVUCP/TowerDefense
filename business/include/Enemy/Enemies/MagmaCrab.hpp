#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class MagmaCrab : public BaseEnemy {
public:
  static constexpr int VELOCITY = 3;
  static constexpr int KILL_COINS = 1;
  static constexpr int INITIAL_HEALTH = 10;

public:
  MagmaCrab(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
