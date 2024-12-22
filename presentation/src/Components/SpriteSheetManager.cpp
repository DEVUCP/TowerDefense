#include "Components/SpriteSheetManager.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"

void SpriteSheetManager::load_sheet(sf::Sprite& sprite, sf::Texture& texture,
                                    std::string sheet_path) {
  if (!texture.loadFromFile(sheet_path)) {
    std::cerr << "Texture not found: " << sheet_path << std::endl;
    exit(1);
  }
  sprite.setTexture(texture);
  current_index = -1;
  maximum_count_per_row = sprite.getGlobalBounds().width / width;
}

void SpriteSheetManager::set_width(unsigned wid) { width = wid; }
void SpriteSheetManager::set_height(unsigned hei) { height = hei; }

void SpriteSheetManager::register_collection(std::string identifier,
                                             int row_num, int count,
                                             int row_count) {
  info[identifier].row_num = row_num;
  info[identifier].count = count == -1 ? maximum_count_per_row : count;
  info[identifier].row_count = row_count;
}

void SpriteSheetManager::set_collection(std::string cur) {
  current_collection = cur;
}

void SpriteSheetManager::next_sprite(sf::Sprite& sprite) {
  time_elapsed += clock.restart();

  // Check if the elapsed time exceeds the animation delay
  if (time_elapsed.asMilliseconds() < ANIMATION_DELAY) return;

  assert(!current_collection.empty());

  time_elapsed -= sf::milliseconds(ANIMATION_DELAY);

  if (info.find(current_collection) == info.end())
    throw std::runtime_error("No current collection");

  auto collection = info[current_collection];

  unsigned total =
      (collection.row_count - 1) * maximum_count_per_row + collection.count;
  current_index = (current_index + 1) % total;
  int offsetY = collection.row_num * height;
  int x = (current_index % total) * width,
      y = offsetY + (current_index / total) * height;
  sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void SpriteSheetManager::set_initial_sprite(sf::Sprite& sprite) {
  auto collection = info[current_collection];
  int offset = collection.row_num * height;
  int x = 0, y = offset;
  sprite.setTextureRect(sf::IntRect(x, y, x + width, y + height));

  // Initialize time_elapsed
  time_elapsed = sf::Time::Zero;
}
