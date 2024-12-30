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
  for (auto& att : attacks) {
  }
  std::cout << "Attacks Size: " << attacks.size() << std::endl;
}

void AttackManager::filter_attacks() {
  for (auto itr = attacks.begin(); itr != attacks.end();)
    if ((*itr)->is_to_be_removed()) {
      itr = attacks.erase(itr);
    } else
      itr++;
}
