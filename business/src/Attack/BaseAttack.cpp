#include "Attack/BaseAttack.hpp"

BaseAttack::BaseAttack(float x, float y, float width, float height,
                       float velocity, Vector<float> target,
                       const std::string& sprite, int damage)
    : Moveable(x, y, velocity, target),
      Collidable(x, y, width, height),
      damage(damage) {}

bool BaseAttack::is_to_be_removed() {}

bool BaseAttack::hit(std::shared_ptr<BaseEnemy> enemy) {}

void BaseAttack::on_hit() {}

void on_reach() {}
void BaseAttack::on_out_of_board() {}
