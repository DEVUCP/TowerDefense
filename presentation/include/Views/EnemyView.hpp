#pragma once

#include <memory>
#include "Enemy/BaseEnemy.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Texture.hpp"
class EnemyView : public Widget {
public:
  EnemyView(std::shared_ptr<BaseEnemy>);

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  std::shared_ptr<BaseEnemy> enemy;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
};
