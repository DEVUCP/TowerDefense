#include "Views/EnemyView.hpp"
#include <memory>
#include "GameSettings.hpp"
#include "Interfaces/EventData.hpp"

std::unordered_map<BaseEnemy::EnemyType, std::string> EnemyView::sheets = {
    {BaseEnemy::EnemyType::LEAF_BUG, "./assets/textures/enemies/Leafbug.png"}};

EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm) : enemy(enm) {
  assert(enm != nullptr);
  sheet_mng.load_sheet(sprite, sprite_sheet, sheets[enm->get_type()]);

  // TODO: This is Registration for LeafBug. Make it dynamic tomorrow
  // TODO: Fix These magic numbers by some kind of table
  sheet_mng.set_width(64);
  sheet_mng.set_height(64);
  sheet_mng.register_collection("LEFT_MOVEMENT", 5, 8);
  sheet_mng.set_collection("LEFT_MOVEMENT");
  sheet_mng.init_sprite_texture(sprite);

  // Scale up to desired
  auto width = GameSettings::get_instance().get_enemy_width();
  auto height = GameSettings::get_instance().get_enemy_height();
  sprite.setScale(sf::Vector2f(width / 64.f, height / 64.f));
  sprite.setOrigin(width / 2.f, height / 2.f);
}

void EnemyView::handle_events(EventData evt) {}
void EnemyView::update(UpdateData dat) {
  auto pos = enemy->get_position();
  sprite.setPosition(pos.x, pos.y);
  sheet_mng.next_sprite(sprite);
}
void EnemyView::render(RenderData ren) { ren.window->draw(sprite); }

bool EnemyView::is_to_be_removed() const { return enemy->is_to_be_removed(); }
