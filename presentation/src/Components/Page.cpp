#include "Components/Page.hpp"
#include "GameSettings.hpp"

Page::Page(unsigned width, unsigned height)
    : target_width(width), target_height(height) {}

float Page::scale_width(float val) {
  return val * target_width / GameSettings::get_instance().get_size().x;
}
float Page::scale_height(float val) {
  return val * target_height / GameSettings::get_instance().get_size().y;
}
unsigned Page::scale_width(unsigned val) {
  return val * target_width / GameSettings::get_instance().get_size().x;
}
unsigned Page::scale_height(unsigned val) {
  return val * target_height / GameSettings::get_instance().get_size().y;
}
