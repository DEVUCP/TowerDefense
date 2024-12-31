#include "Enemy/Enemies/LeafBug.hpp"
#include <iostream>
#include "Enemy/BaseEnemy.hpp"

LeafBug::LeafBug(float x, float y, Vector<float> dest)
    : BaseEnemy(x, y, dest, INITIAL_HEALTH, VELOCITY, KILL_COINS,
                EnemyType::LEAF_BUG),
      Positionable(x, y) {
  std::cout << "Moving: " << x << " " << y << std::endl;
  std::cout << "Moving to: " << dest.x << " " << dest.y << std::endl;
}

void LeafBug::on_killed() {}
