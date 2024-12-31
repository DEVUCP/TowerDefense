#include "Components/SpriteSheetManager.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"

SpriteSheetManager::SpriteSheetManager()
    : animation_delay(DEFAULT_ANIMATION_DELAY) {}

void SpriteSheetManager::load_sheet(sf::Sprite& sprite, sf::Texture& texture,
                                    std::string sheet_path) {
  if (!texture.loadFromFile(sheet_path)) {
    std::cerr << "Texture not found: " << sheet_path << std::endl;
    exit(1);
  }
  sprite.setTexture(texture);
  current_index = -1;
}

void SpriteSheetManager::set_width(unsigned wid) { width = wid; }
void SpriteSheetManager::set_height(unsigned hei) { height = hei; }

void SpriteSheetManager::register_collection(std::string identifier,
                                             int row_num, int count,
                                             int row_count) {
  info[identifier].row_num = row_num;
  info[identifier].count = count;
  info[identifier].row_count = row_count;
}

void SpriteSheetManager::set_collection(std::string cur) {
  current_collection = cur;
}

void SpriteSheetManager::next_sprite(sf::Sprite& sprite) {
  time_elapsed += clock.restart();

  // Check if the elapsed time exceeds the animation delay
  if (time_elapsed.asMilliseconds() < animation_delay) return;

  assert(!current_collection.empty());

  time_elapsed -= sf::milliseconds(animation_delay);

  if (info.find(current_collection) == info.end())
    throw std::runtime_error("No current collection");

  auto collection = info[current_collection];
  auto maximum_count_per_row =
      sprite.getGlobalBounds().width /
      width;  // TODO: Fails already, load texture instead

  unsigned total =
      (collection.row_count - 1) * maximum_count_per_row + collection.count;
  current_index = (current_index + 1) % total;
  int offsetY = collection.row_num * height;
  int x = (current_index % total) * width,
      y = offsetY + (current_index / total) * height;
  sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void SpriteSheetManager::next_sprite(sf::Sprite& sprite,
                                     std::string collection_name) {
  if (current_collection == collection_name)
    next_sprite(sprite);
  else
    set_collection(collection_name);
}

void SpriteSheetManager::init_sprite_texture(sf::Sprite& sprite) {
  assert(!current_collection.empty());

  if (info.find(current_collection) == info.end())
    throw std::runtime_error("No current collection");

  auto collection = info[current_collection];
  auto maximum_count_per_row = sprite.getGlobalBounds().width / width;

  unsigned total =
      (collection.row_count - 1) * maximum_count_per_row + collection.count;
  current_index = (current_index + 1) % total;
  int offsetY = collection.row_num * height;
  int x = (current_index % total) * width,
      y = offsetY + (current_index / total) * height;
  sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void SpriteSheetManager::scale_animation_delay(unsigned new_value) {
  animation_delay = new_value * DEFAULT_ANIMATION_DELAY;
}

std::string SpriteSheetManager::get_current_collection() const {
  return current_collection;
}

void SpriteSheetManager::handle_reverse(bool value, sf::Sprite spr) {
  if (value == reversed) return;
  reverse_sprite(spr);
  reversed = value;
}

void SpriteSheetManager::reverse_sprite(sf::Sprite& spr) {
  auto current_scale = spr.getScale();
  spr.setScale(-1 * current_scale.x, -1 * current_scale.y);
}

unsigned SpriteSheetManager::get_current_index() { return current_index; }
