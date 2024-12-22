#pragma once

#include <memory>
#include <unordered_map>
#include "Components/SpriteSheetManager.hpp"
#include "Enemy/BaseEnemy.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Texture.hpp"

#define SPRITE_WIDTH 64
#define SPRITE_HEIGHT 64
#define DESIRED_SPRITE_WIDTH 120
#define DESIRED_SPRITE_HEIGHT 120

class EnemyView : public Widget {
public:
  EnemyView(std::shared_ptr<BaseEnemy>);

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

private:
  std::shared_ptr<BaseEnemy> enemy;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
  SpriteSheetManager sheet_mng;
  static std::unordered_map<BaseEnemy::EnemyType, std::string> sheets;
};
