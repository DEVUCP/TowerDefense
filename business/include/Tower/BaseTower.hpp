#pragma once

#include "Enemy/BaseEnemy.hpp"
#include "Upgrade.hpp"
#include "Utils/Drawable.hpp"

class BaseTower : public Drawable {
public:
  BaseTower();

private:
  Vector<int> position;
  float range;
  float damage;
  std::shared_ptr<Upgrade> offer_upgrades;
  std::shared_ptr<Upgrade> upgrades;
  std::string sprite;
  std::string rotation;
};
