#include "Views/EnemyView.hpp"
#include <memory>
#include "Interfaces/EventData.hpp"

std::unordered_map<BaseEnemy::EnemyType, std::string> EnemyView::sheets = {
    {BaseEnemy::EnemyType::LEAF_BUG,
     "./assets/textures/enemies/Flying Locust.png"}};

EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm) : enemy(enm) {
  sheet_mng.load_sheet(sprite, sprite_sheet, sheets[enm->get_type()]);

  // TODO: This is Registration for LeafBug. Make it dynamic tomorrow
  sheet_mng.register_collection("DOWN_MOVEMENT", 0, 12);
  sheet_mng.set_collection("DOWN_MOVEMENT");
  sheet_mng.set_width(SPRITE_WIDTH);
  sheet_mng.set_height(SPRITE_HEIGHT);
  sheet_mng.set_initial_sprite(sprite);

  // Scale up to desired
  sprite.setScale(
      sf::Vector2f(static_cast<float>(DESIRED_SPRITE_WIDTH) / SPRITE_WIDTH,
                   static_cast<float>(DESIRED_SPRITE_HEIGHT) / SPRITE_HEIGHT));
}

void EnemyView::handle_events(EventData evt) {}
void EnemyView::update(UpdateData dat) {
  auto pos = enemy->get_position();
  sprite.setPosition(pos.x, pos.y);
  sheet_mng.next_sprite(sprite);
}
void EnemyView::render(RenderData ren) { ren.window->draw(sprite); }
