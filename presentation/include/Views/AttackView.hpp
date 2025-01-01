#pragma once
#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include "Attack/BaseAttack.hpp"
#include "Components/SpriteSheetManager.hpp"
#include "Interfaces/Widget.hpp"

class AttackView : public Widget {
private:
  static const inline std::string FILE_PATH = "./data/attack_info.txt";

private:
  struct AttackInfo {
    std::string texture_path;
    std::array<int, 3> widths;
    std::array<int, 3> heights;
    std::array<int, 3> num_of_sprites;
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

  static void load_attack_info();

private:
  std::shared_ptr<BaseAttack> attack;
  sf::Texture sprite_sheet;
  sf::Sprite sprite;
  SpriteSheetManager sheet_mng;
  static std::unordered_map<BaseAttack::AttackType, AttackInfo> attack_info;
};
