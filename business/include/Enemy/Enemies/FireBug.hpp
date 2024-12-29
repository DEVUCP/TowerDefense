#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class FireBug : public BaseEnemy {
public:
  static constexpr int VELOCITY = 4;
  static constexpr int KILL_COINS = 6;
  static constexpr int INITIAL_HEALTH = 12;

public:
  FireBug(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
