#pragma once

#include <memory>
#include "Map/BaseTile.hpp"
#include "Tower/BaseTower.hpp"

class BuildableTile : public BaseTile {
public:
  BuildableTile(float x, float y);
  /*
   * @brief Set a tower
   */
  // void set_tower(std::shared_ptr<BaseTower> tower);

  /*
   * @brief Get a tower
   */
  // std::shared_ptr<BaseTower> get_tower() const;

  /*
   * @brief Remove the current tower
   *
   * @details check if there's a current tower before removal
   */
  // void remove_tower();

private:
  std::shared_ptr<BaseTower> tower;
};
