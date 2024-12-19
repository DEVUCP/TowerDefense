#include "Widgets/MuteButton.hpp"
#include <iostream>
#include "Components/IconButton.hpp"
#include "Components/MusicPlayer.hpp"

MuteButton::MuteButton(unsigned x, unsigned y)
    : IconButton("./assets/buttons/SoundOn.png",
                 "./assets/buttons/SoundOn_Hover.png", x, y) {
  set_handler([]() { MusicPlayer::get_instance().toggle(); });
  check_status();
}

void MuteButton::on_click() {
  IconButton::on_click();
  check_status();
}

void MuteButton::check_status() {
  bool is_playing = MusicPlayer::get_instance().is_playing();
  init_image(is_playing ? "./assets/buttons/SoundOn.png"
                        : "./assets/buttons/SoundOff.png",
             is_playing ? "./assets/buttons/SoundOn_Hover.png"
                        : "./assets/buttons/SoundOff_Hover.png");
}
