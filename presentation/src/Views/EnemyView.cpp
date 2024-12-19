#include "Views/EnemyView.hpp"
#include <memory>
#include <stdexcept>

EnemyView::EnemyView(std::shared_ptr<BaseEnemy> enm) : enemy() {
  switch (enemy->get_type()) {
    case BaseEnemy::EnemyType::LEAF_BUG:
      sprite_sheet.loadFromFile("./assets/textures/enemies/leafbug.png");
      break;
    default:
      throw std::runtime_error(
          "Assets are not loaded for all types of monsters");
  }
  sprite.setTexture(sprite_sheet);
}

void EnemyView::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(sprite);
}
