#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Utils/Vector.hpp"
class MagmaCrab : public BaseEnemy {
public:
  static constexpr int velocity = 3;
  static constexpr int kill_coins = 1;

public:
  MagmaCrab(float x, float y, Vector<float> dest);

private:
  virtual void on_reach() override;
  virtual void on_out_of_board() override;
  virtual void on_killed() override;
};
