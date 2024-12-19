#include "Components/SFXPlayer.hpp"
#include <iostream>

std::unordered_map<SFXPlayer::SoundEffect, std::string> SFXPlayer::effects = {{
    SFXPlayer::BUTTON_CLICK,
    "./assets/sfx/button_click.wav",
}};

SFXPlayer& SFXPlayer::get_instance() {
  static SFXPlayer m;
  return m;
}

void SFXPlayer::play(SoundEffect eff) {
  if (!buffer.loadFromFile(effects[eff])) {
    std::cerr << "failed to load sound effect: " << effects[eff];
    exit(1);
  }
  sound_effect.setBuffer(buffer);
  sound_effect.play();
}
