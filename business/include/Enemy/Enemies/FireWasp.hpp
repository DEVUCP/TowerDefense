#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class FireWasp : public BaseEnemy {
public:
  static constexpr int VELOCITY = 8;
  static constexpr int KILL_COINS = 5;
  static constexpr int INITIAL_HEALTH = 2;

public:
  FireWasp(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
