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

public:
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
   * @param count The count of sprites in the ending row (if count = -1, set to
   * default)
   * @param row_count The number of rows that represent this info
   */
  void register_collection(std::string identifier, int row_num, int count = -1,
                           int row_count = 1);

  /**
   * @brief Move To the next sprite in the current collection
   */
  void next_sprite(sf::Sprite& sprite);

  /**
   * @brief Change current collection
   */
  void set_collection(std::string);

  /**
   * @brief Getter for sprite
   */

private:
  unsigned width;
  unsigned height;
  std::map<std::string, SpriteCollectionInfo>
      info;  // < This holds the data for every row
  std::string current_collection;
  unsigned current_index;
  unsigned maximum_count_per_row;
};
