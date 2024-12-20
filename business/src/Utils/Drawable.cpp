#include "Utils/Drawable.hpp"

Drawable::Drawable(const std::string& sprite, Vector<float> size)
    : size(size), sprite(sprite) {}

const Vector<float>& Drawable::get_size() const { return size; }

const std::string& Drawable::get_sprite() const { return sprite; }
