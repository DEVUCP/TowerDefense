#pragma once

#include <SFML/Audio.hpp>

#include <unordered_map>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
class SFXPlayer {
public:
  enum SoundEffect {
    GAME_START,
    GAME_OVER,
    GAME_WIN,
    BUTTON_CLICK,
  };

public:
  // remove copying
  SFXPlayer(const SFXPlayer&) = delete;
  SFXPlayer operator=(const SFXPlayer&) = delete;

  /**
   * @brief get instance
   */
  static SFXPlayer& get_instance();
  /*
   * @brief Play a sound effect
   */
  void play(SoundEffect);

private:
  SFXPlayer() = default;

private:
  static std::unordered_map<SoundEffect, std::string> effects;
  sf::SoundBuffer buffer;
  sf::Sound sound_effect;
};
