#include "Views/EnemyView.hpp"
#include <memory>
#include "Interfaces/EventData.hpp"

std::unordered_map<BaseEnemy::EnemyType, std::string> EnemyView::sheets = {
    {BaseEnemy::EnemyType::LEAF_BUG, "./assets/textures/enemies/Leafbug.png"}};

EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm) : enemy(enm) {
  sheet_mng.load_sheet(sprite, sprite_sheet, sheets[enm->get_type()]);

  // TODO: This is Registration for LeafBug. Make it dynamic tomorrow
  sheet_mng.register_collection("DOWN_MOVEMENT", 0, 6);
  sheet_mng.set_collection("DOWN_MOVEMENT");
  sheet_mng.set_width(64);
  sheet_mng.set_height(64);
  sheet_mng.next_sprite(sprite);
}

void EnemyView::handle_events(EventData evt) {}
void EnemyView::update() {
  auto pos = enemy->get_position();
  sprite.setPosition(pos.x, pos.y);
  sheet_mng.next_sprite(sprite);
}
void EnemyView::render(RenderData ren) { ren.window->draw(sprite); }
