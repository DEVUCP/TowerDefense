#include "Widgets/MuteButton.hpp"
#include <iostream>
#include "Components/IconButton.hpp"
#include "Components/MusicPlayer.hpp"

MuteButton::MuteButton(unsigned x, unsigned y)
    : IconButton("./assets/buttons/SoundOn.png",
                 "./assets/buttons/SoundOn_Hover.png", x, y,
                 StandardButton::ButtonSize::DEFAULT,
                 StandardButton::ButtonType::SQUARE),
      on{true} {
  set_handler([]() { MusicPlayer::get_instance().toggle(); });
}

void MuteButton::on_click() {
  IconButton::on_click();
  on = !on;
  set_icon_texture(
      on ? "./assets/buttons/SoundOn.png" : "./assets/buttons/SoundOff.png",
      on ? "./assets/buttons/SoundOn_Hover.png"
         : "./assets/buttons/SoundOff_Hover.png");
}
