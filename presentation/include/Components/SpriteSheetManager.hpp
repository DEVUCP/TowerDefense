#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"

class SpriteSheetManager {
private:
  struct SpriteCollectionInfo {
    int row_num;    // < Represent the starting row num for this collection
    int count;      // < Represent the number of sprites in the last row
    int row_count;  // < Represent the number of rows in this collection
  };

private:
  static constexpr float DEFAULT_ANIMATION_DELAY = 50;

public:
  SpriteSheetManager();
  /**
   * @brief Load the texture
   */
  void load_sheet(sf::Sprite& sprite, sf::Texture& texture, std::string);

  /**
   * @brief Set Sprite Width
   */
  void set_width(unsigned width);

  /**
   * @brief Set Sprite height
   */
  void set_height(unsigned width);

  /**
   * @brief Set information for each row.
   *
   * @details Set by default that the number of sprites in a row is sheet_width
   * / sprite_width
   *
   * @param identifier The name for the collection (e.g. movement, spawn)
   * @param row_num The starting row for these collections in the sheets
   * @param count The count of sprites in the ending row
   * @param row_count The number of rows that represent this info
   */
  void register_collection(std::string identifier, int row_num, int count,
                           int row_count = 1);

  /**
   * @brief Move To the next sprite in the current collection
   */
  void next_sprite(sf::Sprite& sprite);

  /**
   * @brief Move To the next sprite in the current collection if it's the same
   * as the collection_name, or move to that other collection
   */
  void next_sprite(sf::Sprite& sprite, std::string collection_name);

  /**
   * @brief Reset the sequence of sprite animation
   */
  unsigned get_current_index();

  /**
   * @brief Change current collection
   */
  void set_collection(std::string);

  /**
   * @brief Initialize the sprite with the first texture
   */
  void init_sprite_texture(sf::Sprite& sprite);

  /**
   * @brief Update the animation delay value in milliseconds relative to the
   * DEFAULT_ANIMATION_DELAY
   */
  void scale_animation_delay(unsigned new_value);

  /**
   * @brief Return the current animation name
   */
  std::string get_current_collection() const;

  /**
   * @brief Get the last index in the current collection
   */
  bool get_last_index();

private:
  unsigned width;
  unsigned height;
  std::map<std::string, SpriteCollectionInfo>
      info;  // < This holds the data for every row
  std::string current_collection;
  unsigned current_index;
  sf::Clock clock;
  sf::Time time_elapsed;
  unsigned desired_x, desired_y;
  unsigned animation_delay;
};
