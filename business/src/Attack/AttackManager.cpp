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
  for (auto& att : attacks) {
    att->move_next();  // TODO
  }
}

void AttackManager::filter_attacks() {
  for (auto itr = attacks.begin(); itr != attacks.end();)
    if ((*itr)->is_to_be_removed()) {
      itr = attacks.erase(itr);
      std::cout << "Removing attack " << itr - attacks.begin() << std::endl;
    } else {
      itr++;
    }
}
