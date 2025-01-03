#pragma once
#include <string>
#include <vector>
#include "Map/BuildableTile.hpp"
#include "Views/TileView.hpp"
#include "Views/TowerView.hpp"

class BuildableTileView : public TileView {
public:
  BuildableTileView(std::shared_ptr<BaseTile> tile);

  /**
   * Overrided Functions
   */
  virtual void handle_events(EventData data);
  virtual void render(RenderData);
  virtual void update(UpdateData);

  /**
   * @brief Build a tower on this tile
   */
  bool build_tower(BaseTower::TowerType type);

  /**
   * @brief Upgrade the tower in this tile
   */
  bool upgrade_tower();

  /**
   * @brief Upgrade the tower in this tile
   */
  void sell_tower();

  /**
   * @brief Get the tower poninter
   */
  std::shared_ptr<TowerView> get_tower_view();

private:
  static std::vector<std::string> sheets;
  std::shared_ptr<TowerView> tower;
};
