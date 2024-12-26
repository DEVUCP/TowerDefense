#include "Tower/Towers/IonPrism.hpp"
#include "Tower/BaseTower.hpp"

IonPrism::IonPrism(std::shared_ptr<BaseTile> tile)
    : BaseTower(tile, RANGE, ATTACK_SPEED, ATTACK_DAMAGE, BaseTower::IonPrism) {
}
