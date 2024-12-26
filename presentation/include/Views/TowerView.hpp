#pragma once

#include <memory>
#include <unordered_map>
#include "Components/SpriteSheetManager.hpp"
#include "Interfaces/Widget.hpp"
#include "Tower/BaseTower.hpp"
class TowerView : public Widget {
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
  std::shared_ptr<BaseTower> tower;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
  SpriteSheetManager sheet_mng;
  static std::unordered_map<BaseTower::TowerType, std::string> sheets;
};
