#pragma once

#include <memory>
#include <unordered_map>
#include "Components/SpriteSheetManager.hpp"
#include "Interfaces/Widget.hpp"
#include "Tower/BaseTower.hpp"
class TowerView : public Widget {
public:
  struct TowerInfo {
    std::string tower_sprite;
    std::string tower_weapon;
  };

public:
  static constexpr float TOWER_TILE_FACTOR = 0.6;

public:
  TowerView(std::shared_ptr<BaseTower> tower);
  /**
   * Overrided Functions
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

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
