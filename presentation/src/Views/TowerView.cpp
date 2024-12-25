#include "Views/TowerView.hpp"
#include <memory>
#include <unordered_map>
#include "Tower/BaseTower.hpp"

std::unordered_map<BaseTower::TowerType, std::string> TowerView::sheets = {
    {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
};

TowerView::TowerView(std::shared_ptr<BaseTower> tower) {
  assert(tower != nullptr);
  sheet_mng.load_sheet(sprite, sprite_sheet, sheets[tower->get_type()]);
}

void TowerView::handle_events(EventData data) {}
void TowerView::render(RenderData ren) {
  // TODO: Render Tower
}
void TowerView::update(UpdateData dat) {}
