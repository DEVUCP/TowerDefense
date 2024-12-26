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

  sheet_mng.set_width(64);
  sheet_mng.set_height(128);
  sheet_mng.register_collection("LVL1", 0, 1);
  sheet_mng.set_collection("LVL1");
  sheet_mng.init_sprite_texture(sprite);
  auto pos = tower->get_position();
  sprite.setPosition(pos.x, pos.y);

  sprite.setScale(120.f / 64, 120.f / 64);
}

void TowerView::handle_events(EventData data) {}
void TowerView::render(RenderData ren) { ren.window->draw(sprite); }
void TowerView::update(UpdateData dat) {}

bool TowerView::Comparator::operator()(std::shared_ptr<TowerView> a,
                                       std::shared_ptr<TowerView> b) const {
  auto pos = a->tower->get_position();
  auto other_pos = b->tower->get_position();
  if (pos.y != other_pos.y) return pos.y > other_pos.y;
  return pos.x > other_pos.x;
}
