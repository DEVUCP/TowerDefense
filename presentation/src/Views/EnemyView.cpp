#include "Views/EnemyView.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include "GameSettings.hpp"
#include "Interfaces/EventData.hpp"

#define LEFT_MOVEMENT "LEFT_MOVEMENT"
#define UP_MOVEMENT "UP_MOVEMENT"
#define DOWN_MOVEMENT "DOWN_MOVEMENT"
#define LEFT_DESTRUCTION "LEFT_DESTRUCTION"
#define UP_DESTRUCTION "UP_DESTRUCTION"
#define DOWN_DESTRUCTION "DOWN_DESTRUCTION"

std::unordered_map<BaseEnemy::EnemyType, EnemyView::EnemyInfo>
    EnemyView::enemies_info = {};

EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm) : enemy(enm) {
  assert(enm != nullptr);
  auto& [texture_path, size, collections] = enemies_info[enm->get_type()];
  sheet_mng.load_sheet(sprite, sprite_sheet, texture_path);

  sheet_mng.set_width(size.first);
  sheet_mng.set_height(size.second);
  for (auto& clc : collections) {
    auto& [name, row, count] = clc;
    sheet_mng.register_collection(name, row, count);
  }
  sheet_mng.set_collection(
      "LEFT_MOVEMENT");  // TODO: Get the current collection
  sheet_mng.init_sprite_texture(sprite);

  // Scale up to desired
  auto width = GameSettings::get_instance().get_enemy_width();
  auto height = GameSettings::get_instance().get_enemy_height();
  sprite.setScale(sf::Vector2f(width / size.first, height / size.second));
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

// EnemyName AssetName [CollectionName,row,count]*
void EnemyView::load_enemy_info() {
  std::ifstream file(FILE_PATH);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open towers info file: " + FILE_PATH);
  }

  enemies_info.clear();  // Clear existing data if any
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;

    std::istringstream line_stream(line);
    std::string enemy_name, asset_name;
    line_stream >> enemy_name >> asset_name;

    BaseEnemy::EnemyType type;

    if (enemy_name == "LEAF_BUG")
      type = BaseEnemy::EnemyType::LEAF_BUG;
    else if (enemy_name == "MAGMA_CRAB")
      type = BaseEnemy::EnemyType::MAGMA_CRAB;
    else if (enemy_name == "CLAMP_BEETLE")
      type = BaseEnemy::EnemyType::CLAMP_BEETLE;
    else
      throw std::runtime_error("Unknown enemy data: " + enemy_name);

    // Read Size
    float width, height;
    line_stream >> width >> height;

    // Read the remaining parts of the line (the collections and counts)
    std::vector<std::tuple<std::string, int, int>> collections;
    std::string collection_name;
    int row, count;

    while (line_stream >> collection_name >> row >> count) {
      collections.push_back(std::make_tuple(collection_name, row, count));
    }

    enemies_info[type] = {asset_name, {width, height}, collections};
  }
}

std::shared_ptr<BaseEnemy> EnemyView::get_enemy() const { return enemy; }
