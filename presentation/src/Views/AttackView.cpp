#include "Views/AttackView.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include "Attack/BaseAttack.hpp"

std::unordered_map<BaseAttack::AttackType, AttackView::AttackInfo>
    AttackView::attack_info = {
        {BaseAttack::ARCHERY_ATTACK,
         {"./assets/textures/attacks/ArcheryTower_Projectiles.png"}}};

AttackView::AttackView(std::shared_ptr<BaseAttack> attack) : attack{attack} {
  assert(attack != nullptr);

  sheet_mng.load_sheet(sprite, sprite_sheet,
                       attack_info[attack->get_type()].texture_path);
  // TODO: Fix this magic numbers
  sheet_mng.set_width(8);
  sheet_mng.set_height(40);
  sheet_mng.register_collection("LVL1", 0, 3);
  sheet_mng.set_collection("LVL1");
  sheet_mng.init_sprite_texture(sprite);

  // Set Rotation
  sprite.setRotation(attack->get_rotation() + 90);

  // Set Origin
  auto bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void AttackView::handle_events(EventData data) {}
void AttackView::render(RenderData ren) { ren.window->draw(sprite); }
void AttackView::update(UpdateData) {
  auto pos = attack->get_position();
  sprite.setPosition(pos.x, pos.y);
  sheet_mng.next_sprite(sprite);
}

bool AttackView::is_to_be_removed() const { return attack->is_to_be_removed(); }
