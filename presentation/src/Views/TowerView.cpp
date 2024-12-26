#include "Views/TowerView.hpp"
#include <memory>
#include <tuple>
#include <unordered_map>
#include "GameSettings.hpp"
#include "Tower/BaseTower.hpp"

std::unordered_map<BaseTower::TowerType, TowerView::TowerInfo>
    TowerView::towers_info = {
        {BaseTower::IonPrism,
         {
             "./assets/textures/towers/IonPrism.png",
             "./assets/textures/attacks/IonPrism/lvl1.png",
         }}};

TowerView::TowerView(std::shared_ptr<BaseTower> tower) : tower(tower) {
  init_tower_sprite();
  init_weapon_sprite();
}

void TowerView::init_tower_sprite() {
  assert(tower != nullptr);

  // Initialize the sheet manager
  tower_sprite_mng.load_sheet(sprite, sprite_sheet,
                              towers_info[tower->get_type()].tower_sprite);
  tower_sprite_mng.set_width(64);
  tower_sprite_mng.set_height(128);
  tower_sprite_mng.register_collection("LVL1", 0, 1);
  tower_sprite_mng.set_collection("LVL1");
  tower_sprite_mng.init_sprite_texture(sprite);

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

void TowerView::init_weapon_sprite() {
  // Handle the change in levels
  weapon_sprite_mng.load_sheet(weapon, weapon_texture,
                               towers_info[tower->get_type()].tower_weapon);
  weapon_sprite_mng.set_width(64);
  weapon_sprite_mng.set_height(64);
  weapon_sprite_mng.register_collection("LVL1", 0, 6);
  weapon_sprite_mng.set_collection("LVL1");
  weapon_sprite_mng.init_sprite_texture(weapon);

  // TODO: Position the weapon correctly
  auto pos = tower->get_position();
  auto tile_len = GameSettings::get_instance().get_tile_size();
  pos.x += tile_len / 2.f * (1 - TOWER_TILE_FACTOR);
  pos.y -= (tile_len / 2.f * (TOWER_TILE_FACTOR)) -
           27;  // TODO: Fix this magic number by doing maths
  weapon.setPosition(pos.x, pos.y);

  // Set Scale to the sprite
  // NOTE: Scale as much as the tower has been scaled
  weapon.setScale(TOWER_TILE_FACTOR * 120.f / 64,
                  TOWER_TILE_FACTOR * 120.f / 64);
}
void TowerView::handle_events(EventData data) {}
void TowerView::render(RenderData ren) {
  ren.window->draw(sprite);
  ren.window->draw(weapon);
  weapon_sprite_mng.next_sprite(weapon);
}
void TowerView::update(UpdateData dat) {}
