#pragma once

#include "Components/IconButton.hpp"
class MuteButton : public IconButton {
public:
  MuteButton(unsigned x, unsigned y);

  void on_click() override;

  void check_status();
};
