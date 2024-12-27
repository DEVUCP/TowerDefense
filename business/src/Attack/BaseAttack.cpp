#include "Attack/BaseAttack.hpp"
#include <algorithm>

BaseAttack::BaseAttack(float x, float y, float width, float height,
                       float velocity, Vector<float> target,
                       const std::string& sprite, int damage)
    : Moveable(x, y, velocity, target),
      Collidable(x, y, width, height),
      damage(damage) {}

bool BaseAttack::is_to_be_removed() { return to_be_removed; }

void BaseAttack::check_collisions(std::shared_ptr<Map> map) {}

std::vector<std::shared_ptr<BaseTile>> BaseEnemy::filter_tiles(
    std::vector<std::shared_ptr<BaseTile>> nearby) {}

std::vector<std::shared_ptr<BaseTile>> BaseEnemy::get_nearby_tiles(
    std::shared_ptr<Map> map) {}

bool BaseAttack::hit(std::shared_ptr<BaseEnemy> enemy) {}

void BaseAttack::on_hit() {}

void BaseAttack::on_reach() { to_be_removed = true; }
void BaseAttack::on_out_of_board() { to_be_removed = true; }
