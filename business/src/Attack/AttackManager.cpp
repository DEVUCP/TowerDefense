#include "Attack/AttackManager.hpp"
#include <algorithm>
#include <iostream>
#include "Attack/BaseAttack.hpp"

void AttackManager::register_attack(std::shared_ptr<BaseAttack> att) {
  attacks.push_back(att);
}

void AttackManager::remove_attack(std::shared_ptr<BaseAttack> att) {
  attacks.erase(std::find(attacks.begin(), attacks.end(), att));
}

void AttackManager::move_attacks() {
  for (auto& att : attacks) att->move_next();
}

void AttackManager::filter_attacks(
    std::function<void(std::shared_ptr<BaseAttack>)> on_attack_hit,
    std::function<void(std::shared_ptr<BaseAttack>)> on_attack_out_of_bound) {
  for (auto itr = attacks.begin(); itr != attacks.end();)
    switch ((*itr)->get_state()) {
      case BaseAttack::MOVING:
        itr++;
        break;
      case BaseAttack::HIT:
        on_attack_hit(*itr);
        itr = attacks.erase(itr);
        break;
      case BaseAttack::OUT:
        on_attack_out_of_bound(*itr);
        itr = attacks.erase(itr);
        break;
    }
}
