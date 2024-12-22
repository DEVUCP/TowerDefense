#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class LeafBug : public BaseEnemy {
public:
  static constexpr int velocity = 3;
  static constexpr int kill_coins = 1;
  static constexpr int initial_health = 10;

public:
  LeafBug(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
