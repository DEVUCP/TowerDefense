#pragma once

#include <array>
#include <memory>
#include <unordered_map>
#include "Components/SpriteSheetManager.hpp"
#include "Interfaces/Widget.hpp"
#include "Tower/BaseTower.hpp"
class TowerView : public Widget {
private:
  struct TowerInfo {
    std::string tower_sprite;
    std::string tower_weapon;
    std::array<int, 3> attack_offset;
    std::pair<int, int> attack_size;
    std::array<int, 3> num_of_sprites;
    std::array<int, 3> shooting_sprite_index;
  };

public:
  static constexpr float TOWER_TILE_FACTOR = 0.6;
  static constexpr float WEAPON_SPRITE_LEN = 64.f;
  static const inline std::string FILE_PATH = "./data/tower_info.txt";

public:
  TowerView(std::shared_ptr<BaseTower> tower);
  /**
   * Overrided Functions
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief Initialize the tower_info data
   *
   * @Details Must be called while the game is uplaoding
   */
  static void load_tower_info();

  /**
   * @brief Get the tower poninter
   */
  std::shared_ptr<BaseTower> get_tower();


private:
  /**
   * @brief Initialize the tower sprite manager
   */
  void init_tower_sprite();

  /**
   * @brief Initialize the weapon sprite manager
   */
  void init_weapon_sprite();

private:
  std::shared_ptr<BaseTower> tower;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
  SpriteSheetManager tower_sprite_mng;
  sf::Texture weapon_texture;
  sf::Sprite weapon;
  SpriteSheetManager weapon_sprite_mng;
  static std::unordered_map<BaseTower::TowerType, TowerInfo> towers_info;
};
