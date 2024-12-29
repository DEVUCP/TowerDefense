#include "Views/EnemyView.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include "GameSettings.hpp"
#include "Interfaces/EventData.hpp"

#define LEFT_MOVEMENT "LEFT_MOVEMENT"
#define UP_MOVEMENT "UP_MOVEMENT"
#define DOWN_MOVEMENT "DOWN_MOVEMENT"
#define LEFT_DESTRUCTION "LEFT_DESTRUCTION"
#define UP_DESTRUCTION "UP_DESTRUCTION"
#define DOWN_DESTRUCTION "DOWN_DESTRUCTION"

std::unordered_map<BaseEnemy::EnemyType, EnemyView::EnemyInfo>
    EnemyView::enemies_info = {
        {BaseEnemy::EnemyType::LEAF_BUG,
         {"./assets/textures/enemies/LeafBug.png",
          {
              {LEFT_MOVEMENT, 5, 8},
              {UP_MOVEMENT, 4, 8},
              {DOWN_MOVEMENT, 3, 8},
              {LEFT_DESTRUCTION, 5 + 3, 8},
              {UP_DESTRUCTION, 4 + 3, 8},
              {DOWN_DESTRUCTION, 3 + 3, 8},
          }}},
        {BaseEnemy::EnemyType::MAGMA_CRAB,
         {"./assets/textures/enemies/MagmaCrab.png",
          {
              {LEFT_MOVEMENT, 5, 8},
              {UP_MOVEMENT, 4, 8},
              {DOWN_MOVEMENT, 3, 8},
              {LEFT_DESTRUCTION, 5 + 3, 8},
              {UP_DESTRUCTION, 4 + 3, 8},
              {DOWN_DESTRUCTION, 3 + 3, 8},
          }}},
        {BaseEnemy::EnemyType::CLAMP_BEETLE,
         {"./assets/textures/enemies/ClampBeetle.png",
          {
              {LEFT_MOVEMENT, 5, 8},
              {UP_MOVEMENT, 4, 8},
              {DOWN_MOVEMENT, 3, 8},
              {LEFT_DESTRUCTION, 5 + 3, 8},
              {UP_DESTRUCTION, 4 + 3, 8},
              {DOWN_DESTRUCTION, 3 + 3, 8},
          }}},
};

EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm) : enemy(enm) {
  assert(enm != nullptr);
  auto& [texture_path, collections] = enemies_info[enm->get_type()];
  sheet_mng.load_sheet(sprite, sprite_sheet, texture_path);

  // TODO: This is Registration for LeafBug. Make it dynamic tomorrow
  // TODO: Fix These magic numbers by some kind of table
  sheet_mng.set_width(64);
  sheet_mng.set_height(64);
  for (auto& clc : collections) {
    auto& [name, row, count] = clc;
    sheet_mng.register_collection(name, row, count);
  }
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
  int angle = enemy->get_rotation();
  sprite.setPosition(pos.x, pos.y);
  switch (angle) {
    case 0:
      sheet_mng.next_sprite(sprite, LEFT_MOVEMENT);
      sheet_mng.handle_reverse(false, sprite);
      break;
    case 90:
      sheet_mng.next_sprite(sprite, DOWN_MOVEMENT);
      sheet_mng.handle_reverse(false, sprite);
      break;
    case 270:
      sheet_mng.next_sprite(sprite, UP_MOVEMENT);
      sheet_mng.handle_reverse(false, sprite);
      break;
    case 180:
      sheet_mng.next_sprite(sprite, LEFT_MOVEMENT);
      sheet_mng.handle_reverse(true, sprite);
      break;
    default:
      throw std::runtime_error(
          "Current game doesn't support enemies moving in directions other "
          "than the 4 axes");
  }
}
void EnemyView::render(RenderData ren) { ren.window->draw(sprite); }

bool EnemyView::is_to_be_removed() const { return enemy->is_to_be_removed(); }
