#pragma once
#include <memory>
#include <unordered_map>
#include "Attack/BaseAttack.hpp"
#include "Components/SpriteSheetManager.hpp"
#include "Interfaces/Widget.hpp"

class AttackView : public Widget {
private:
  struct AttackInfo {
    std::string texture_path;
  };

public:
  AttackView(std::shared_ptr<BaseAttack>);

  /*
   * Overrided Methods
   */
  void handle_events(EventData data);
  void render(RenderData);
  void update(UpdateData);

  /**
   * @brief Getter for `attack`
   */

  std::shared_ptr<BaseAttack> get_attack() const;

private:
  std::shared_ptr<BaseAttack> attack;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
  SpriteSheetManager sheet_mng;
  static std::unordered_map<BaseAttack::AttackType, AttackInfo> attack_info;
};
