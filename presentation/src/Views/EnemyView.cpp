#include "Views/EnemyView.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include "Enemy/BaseEnemy.hpp"
#include "GameSettings.hpp"
#include "Interfaces/EventData.hpp"

#define LEFT_MOVEMENT "LEFT_MOVEMENT"
#define RIGHT_MOVEMENT "LEFT_MOVEMENT"
#define UP_MOVEMENT "UP_MOVEMENT"
#define DOWN_MOVEMENT "DOWN_MOVEMENT"
#define LEFT_DESTRUCTION "LEFT_DESTRUCTION"
#define RIGHT_DESTRUCTION "LEFT_DESTRUCTION"
#define UP_DESTRUCTION "UP_DESTRUCTION"
#define DOWN_DESTRUCTION "DOWN_DESTRUCTION"

std::unordered_map<BaseEnemy::EnemyType, EnemyView::EnemyInfo>
    EnemyView::enemies_info = {};
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& pair) const {
    return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
  }
};
EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm)
    : enemy(enm), removed(false) {
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

  // Set Origin
  auto bounds = sprite.getGlobalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void EnemyView::handle_events(EventData evt) {}
void EnemyView::update(UpdateData dat) {
  auto state = enemy->get_state();
  if (state == BaseEnemy::DEAD &&
      sheet_mng.get_current_index() == sheet_mng.get_last_index()) {
    removed = true;
    return;
  }

  auto pos = enemy->get_position();
  int angle = enemy->get_rotation();
  angle =
      ((angle + 45) / 90) * 90 % 360;  // approximate to the nearest 90 degrees
  sprite.setPosition(pos.x, pos.y);

  static const std::unordered_map<std::pair<int, bool>, std::string, pair_hash>
      angle_state_to_collection = {
          {{0, 0}, RIGHT_MOVEMENT},    {{90, 0}, DOWN_MOVEMENT},
          {{270, 0}, UP_MOVEMENT},     {{180, 0}, LEFT_MOVEMENT},
          {{0, 1}, RIGHT_DESTRUCTION}, {{90, 1}, DOWN_DESTRUCTION},
          {{270, 1}, UP_DESTRUCTION},  {{180, 1}, LEFT_DESTRUCTION}};

  auto it = angle_state_to_collection.find({angle, state == BaseEnemy::DEAD});
  if (it == angle_state_to_collection.end())
    throw std::runtime_error(
        "Current game doesn't support enemies moving or destructing in "
        "directions other than the 4 axes. Angle is: " +
        std::to_string(angle));

  const std::string& collection_name = it->second;
  sheet_mng.next_sprite(sprite, collection_name);
  if (state == BaseEnemy::DEAD) {
    sheet_mng.scale_animation_delay(10);
  }
}
void EnemyView::render(RenderData ren) { ren.window->draw(sprite); }

// EnemyName AssetName [CollectionName,row,count]*
void EnemyView::load_enemy_info() {
  std::ifstream file(FILE_PATH);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open enemies info file: " + FILE_PATH);
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
    else if (enemy_name == "FIRE_WASP")
      type = BaseEnemy::EnemyType::FIRE_WASP;
    else if (enemy_name == "SCORPION")
      type = BaseEnemy::EnemyType::SCORPION;
    else if (enemy_name == "FLYING_LOCUST")
      type = BaseEnemy::EnemyType::FLYING_LOCUST;
    else if (enemy_name == "VOID_BUTTERFLY")
      type = BaseEnemy::EnemyType::VOID_BUTTERFLY;
    else
      throw std::runtime_error("Unknown enemy data: " + enemy_name);

    // Read Size
    float width, height;
    line_stream >> width >> height;

    // Read the remaining parts of the line (the collections and counts)
    std::vector<std::tuple<std::string, int, int>> collections;
    std::string collection_name;
    int row, count;

    while (line_stream >> collection_name >> row >> count)
      collections.push_back(std::make_tuple(collection_name, row, count));

    enemies_info[type] = {asset_name, {width, height}, collections};
  }
}

std::shared_ptr<BaseEnemy> EnemyView::get_enemy() const { return enemy; }

bool EnemyView::get_removed() const { return removed; }
