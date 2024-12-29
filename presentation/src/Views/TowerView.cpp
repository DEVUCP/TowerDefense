#include "Views/TowerView.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include "GameSettings.hpp"
#include "Tower/BaseTower.hpp"

// TODO: Store this data somewhere
std::unordered_map<BaseTower::TowerType, TowerView::TowerInfo>
    TowerView::towers_info = {};

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
  auto& [tower_texture_sheet, weapon_texture_sheet, attacks_offsets,
         attacks_size, sprites_number, shooting_sprite] =
      towers_info[tower->get_type()];
  auto& [num1, num2, num3] = sprites_number;

  // Load weapon texture and initialize the sprite
  weapon_sprite_mng.load_sheet(weapon, weapon_texture, weapon_texture_sheet);
  weapon_sprite_mng.set_width(attacks_size.first);  // Width from attacks_size
  weapon_sprite_mng.set_height(
      attacks_size.second);  // Height from attacks_size
  weapon_sprite_mng.register_collection("LVL1", 0, num1);
  weapon_sprite_mng.register_collection("LVL2", 1, num2);
  weapon_sprite_mng.register_collection("LVL3", 2, num3);
  weapon_sprite_mng.set_collection("LVL1");
  weapon_sprite_mng.init_sprite_texture(weapon);

  // Calculate weapon position
  auto pos = tower->get_position();  // Tower position
  auto tile_len = GameSettings::get_instance().get_tile_size();

  // Fetch weapon dimensions from attacks_size

  float weapon_offset_x = (tile_len - WEAPON_SPRITE_LEN) / 2.f;
  float weapon_offset_y = -(tile_len / 2.f * TOWER_TILE_FACTOR) +
                          attacks_offsets[tower->get_level() - 1];
  std::cout << "Y Offset per tower: " << attacks_offsets[tower->get_level() - 1]
            << std::endl;

  // Set weapon position
  pos.x += weapon_offset_x;
  pos.y += weapon_offset_y;
  weapon.setPosition(pos.x, pos.y);
  std::cout << "Position: " << pos.x << " " << pos.y << std::endl;

  // Set scale using attacks_size
  weapon.setScale(WEAPON_SPRITE_LEN / attacks_size.first,
                  WEAPON_SPRITE_LEN / attacks_size.second);
  std::cout << "Width of Weapon: " << weapon.getGlobalBounds().width
            << std::endl;
}
void TowerView::handle_events(EventData data) {}
void TowerView::render(RenderData ren) {
  ren.window->draw(sprite);
  ren.window->draw(weapon);
  if (tower->in_range()) {
    weapon_sprite_mng.next_sprite(weapon);
  }
}
void TowerView::update(UpdateData dat) {}

void TowerView::load_tower_info() {
  std::ifstream file(FILE_PATH);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open towers info file: " + FILE_PATH);
  }

  towers_info.clear();  // Clear existing data if any
  std::string line;

  while (std::getline(file, line)) {
    // Skip comments or empty lines
    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::istringstream line_stream(line);
    std::string tower_name, tower_sprite, weapon_sprite, attack_offsets_str,
        attack_size_str, frame_counts_str, frame_speeds_str;

    // Read all fields from the line
    line_stream >> tower_name >> tower_sprite >> weapon_sprite >>
        attack_offsets_str >> attack_size_str >> frame_counts_str >>
        frame_speeds_str;

    BaseTower::TowerType type;

    // Map string tower names to enum values
    if (tower_name == "ArcheryTower")
      type = BaseTower::ArcheryTower;
    else if (tower_name == "CatapultTower")
      type = BaseTower::CatapultTower;
    else if (tower_name == "SlingshotTower")
      type = BaseTower::SlingshotTower;
    else if (tower_name == "ElectroTower")
      type = BaseTower::ElectroTower;
    else
      throw std::runtime_error("Unknown tower type: " + tower_name);

    // Parse AttackOffsets
    std::vector<int> attack_offsets;
    std::istringstream attack_offsets_stream(attack_offsets_str);
    for (std::string value; std::getline(attack_offsets_stream, value, ',');) {
      attack_offsets.push_back(std::stoi(value));
    }

    // Parse AttackSize
    std::pair<int, int> attack_size;
    std::istringstream attack_size_stream(attack_size_str);
    std::string size_value;
    std::getline(attack_size_stream, size_value, ',');
    attack_size.first = std::stoi(size_value);
    std::getline(attack_size_stream, size_value, ',');
    attack_size.second = std::stoi(size_value);

    // Parse FrameCounts
    std::vector<int> frame_counts;
    std::istringstream frame_counts_stream(frame_counts_str);
    for (std::string value; std::getline(frame_counts_stream, value, ',');) {
      frame_counts.push_back(std::stoi(value));
    }

    // Parse FrameSpeeds
    std::vector<int> frame_speeds;
    std::istringstream frame_speeds_stream(frame_speeds_str);
    for (std::string value; std::getline(frame_speeds_stream, value, ',');) {
      frame_speeds.push_back(std::stoi(value));
    }

    // Construct TowerInfo and insert into map
    TowerInfo info = {tower_sprite,
                      weapon_sprite,
                      {attack_offsets[0], attack_offsets[1], attack_offsets[2]},
                      attack_size,
                      {frame_counts[0], frame_counts[1], frame_counts[2]},
                      {frame_speeds[0], frame_speeds[1], frame_speeds[2]}};

    towers_info[type] = info;
  }

  file.close();
}
