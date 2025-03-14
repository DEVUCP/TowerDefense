#pragma once

#include <memory>
#include <unordered_map>
#include "Components/SpriteSheetManager.hpp"
#include "Enemy/BaseEnemy.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Texture.hpp"

class EnemyView : public Widget {
private:
  struct EnemyInfo {
    std::string texture_path;
    std::pair<float, float> size;
    std::vector<std::tuple<std::string, int, int>> collections;
  };

public:
  static const inline std::string FILE_PATH = "./data/enemy_info.txt";

public:
  EnemyView(std::shared_ptr<BaseEnemy>);

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief Initialize the enemy info
   */
  static void load_enemy_info();

  /**
   * @brief Getter for enemy
   */
  std::shared_ptr<BaseEnemy> get_enemy() const;

  /**
   * @brief Getter for `removed`
   */
  bool get_removed() const;

private:
  std::shared_ptr<BaseEnemy> enemy;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
  SpriteSheetManager sheet_mng;
  static std::unordered_map<BaseEnemy::EnemyType, EnemyInfo> enemies_info;
  bool removed;
};
