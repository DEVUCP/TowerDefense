#include "Views/AttackView.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include "Attack/BaseAttack.hpp"

std::unordered_map<BaseAttack::AttackType, AttackView::AttackInfo>
    AttackView::attack_info;

AttackView::AttackView(std::shared_ptr<BaseAttack> attack) : attack{attack} {
  assert(attack != nullptr);

  auto& [texture_path, widths, heights, nums] = attack_info[attack->get_type()];
  auto lvl_index = attack->get_lvl() - 1;
  auto width = widths[lvl_index];
  auto height = heights[lvl_index];
  std::cout << width << " " << height << std::endl;

  sheet_mng.load_sheet(sprite, sprite_sheet, texture_path);
  sheet_mng.set_width(width);
  sheet_mng.set_height(height);

  // NOTE: Need to register one register
  sheet_mng.register_collection("CUR", lvl_index, nums[lvl_index]);
  sheet_mng.set_collection("CUR");
  sheet_mng.init_sprite_texture(sprite);

  // Set Rotation
  sprite.setRotation(attack->get_rotation() + 90);

  // Set Scale
  // TODO:
  sprite.setScale(1, 1);

  // Set Origin
  // auto bounds = sprite.getLocalBounds();
  // sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void AttackView::handle_events(EventData data) {}
void AttackView::render(RenderData ren) { ren.window->draw(sprite); }
void AttackView::update(UpdateData) {
  auto pos = attack->get_position();
  sprite.setPosition(pos.x, pos.y);
  sheet_mng.next_sprite(sprite);
}

std::shared_ptr<BaseAttack> AttackView::get_attack() const { return attack; }

void AttackView::load_attack_info() {
  std::ifstream file(FILE_PATH);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + FILE_PATH);
  }

  std::string line;
  while (std::getline(file, line)) {
    // Skip comments and empty lines
    if (line.empty() || line[0] == '#') continue;

    std::istringstream stream(line);
    std::string attack_type_str, texture_path;
    std::array<int, 3> widths, heights, num_of_sprites;

    // Read the attack type
    stream >> attack_type_str;

    // Convert the attack type string to BaseAttack::AttackType
    BaseAttack::AttackType attack_type;
    if (attack_type_str == "ARCHERY_ATTACK")
      attack_type = BaseAttack::ARCHERY_ATTACK;
    else if (attack_type_str == "CATAPULT_ATTACK")
      attack_type = BaseAttack::CATAPULT_ATTACK;
    else if (attack_type_str == "ORB_ATTACK")
      attack_type = BaseAttack::ORB_ATTACK;
    else if (attack_type_str == "SLINGSHOT_ATTACK")
      attack_type = BaseAttack::SLINGSHOT_ATTACK;
    else if (attack_type_str == "ELECTRO_ATTACK")
      attack_type = BaseAttack::ELECTRO_ATTACK;
    else if (attack_type_str == "CROSSBOW_ATTACK")
      attack_type = BaseAttack::CROSSBOW_ATTACK;
    else
      throw std::runtime_error("Unknown attack type: " + attack_type_str);

    // Read the texture path
    stream >> texture_path;

    // Read widths, heights, and num_of_sprites
    for (int& width : widths) stream >> width;
    for (int& height : heights) stream >> height;
    for (int& num : num_of_sprites) stream >> num;

    // Populate the map
    attack_info[attack_type] = {texture_path, widths, heights, num_of_sprites};
  }

  file.close();
}
