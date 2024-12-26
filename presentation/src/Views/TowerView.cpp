#include "Views/TowerView.hpp"
#include <memory>
#include <unordered_map>
#include "GameSettings.hpp"
#include "Tower/BaseTower.hpp"

std::unordered_map<BaseTower::TowerType, std::string> TowerView::sheets = {
    {BaseTower::IonPrism, "./assets/textures/towers/IonPrism.png"},
};

TowerView::TowerView(std::shared_ptr<BaseTower> tower) {
  assert(tower != nullptr);

  // Initialize the sheet manager
  sheet_mng.load_sheet(sprite, sprite_sheet, sheets[tower->get_type()]);
  sheet_mng.set_width(64);
  sheet_mng.set_height(128);
  sheet_mng.register_collection("LVL1", 0, 1);
  sheet_mng.set_collection("LVL1");
  sheet_mng.init_sprite_texture(sprite);

  // Set Position with Offset
  auto pos = tower->get_position();
  auto tile_len = GameSettings::get_instance().get_tile_size();
  pos.x += tile_len / 2.f * (1 - TOWER_TILE_FACTOR);
  pos.y -= tile_len / 2.f * (TOWER_TILE_FACTOR);
  sprite.setPosition(pos.x, pos.y);

  // Set Scale to the sprite
  sprite.setScale(TOWER_TILE_FACTOR * 120.f / 64,
                  TOWER_TILE_FACTOR * 120.f / 64);
}

void TowerView::handle_events(EventData data) {}
void TowerView::render(RenderData ren) { ren.window->draw(sprite); }
void TowerView::update(UpdateData dat) {}
