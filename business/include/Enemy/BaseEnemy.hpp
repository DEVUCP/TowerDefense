#pragma once

#include <memory>
#include <queue>
#include "Map/BaseTile.hpp"
#include "Map/Map.hpp"
#include "Utils/Moveable.hpp"
class BaseEnemy : public Moveable {
public:
  enum class EnemyType { LEAF_BUG = 0, MAGMA_CRAB, CLAMP_BEETLE };
  static constexpr int EnemyTypeCount = 3;

public:
  /**
   * @brief Constructor
   *
   * Initialize all variables and call parent constructors
   */
  BaseEnemy(float x, float y, Vector<float> dest, int initial_health,
            float velocity, int kill_coins, EnemyType type);
  /**
   * @brief Update the current tile to be the next tile
   *
   * @details, to do this, use width and height from
   * GameSettings.get_instance().get_width() and get_height(), and use them to
   * calculate the indices of the current tile
   */
  void handle_next_tile_redirection(std::shared_ptr<Map> map);

  /**
   * @brief Getter for health
   */
  const float get_health() const;

  /**
   * @brief Getter for position
   */
  const std::shared_ptr<BaseTile> get_position() const;

  /**
   * @brief Getter for initial health
   */
  const float get_initial_health() const;

  /**
   * @brief Getter for `to_be_removed`
   */
  const bool is_to_be_removed() const;

  /**
   * @brief Invoke damage to enemy
   *
   * @detail If health reaches zero, call `on_killed`
   */
  void invoke_damage(float);

  /**
   * @brief Getter for type
   */
  EnemyType get_type() const;

protected:
  /**
   * @brief A callback to run when the object reaches its destination
   *
   * @details when reaching the next target, update the current tile, and reset
   * the direction to be the next tile by using `handle_next_tile_redirection`
   */
  virtual void on_reach() override;

  /**
   * @brief A callback to run when the object is out of board
   *
   * @details If out of board, invoke damage to player and remove enemy
   */
  virtual void on_out_of_board() override;

  /**
   * @brief A callback to run when the object is killed

   *@details Call EnemyManager to kill self
   */
  virtual void on_killed() = 0;

protected:
  int health;
  int initial_health;
  bool to_be_removed;  // < indicate if the enemy has invoked damage to player
                       // by -1 or has died due to an attack
  int kill_coins;      // represent the amount of money when killing this enemy
  std::queue<std::shared_ptr<BaseTile>>
      current_tile;  // represent the current tile on which the enemy is
  EnemyType type;
};
