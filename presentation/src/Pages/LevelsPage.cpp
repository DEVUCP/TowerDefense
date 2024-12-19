#include "Pages/LevelsPage.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "Components/IconButton.hpp"
#include "Components/LevelButton.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Events/PageEvents.hpp"
#include "Game.hpp"
#include "Widgets/MuteButton.hpp"

LevelsPage::LevelsPage(unsigned w, unsigned h) : Page(w, h) {
  // Initia
  level_count = 8;  // hardcoded for now

  const int ROW_COUNT = 5;                 // 5 levels per row
  const int startx = 440, starty = 400;    // Starting position
  const int offsetx = 250, offsety = 200;  // Spacing between buttons
  // Load the buttons
  for (int i = 0; i < level_count; i++) {
    int column = i % ROW_COUNT;  // Column index (0 to 4)
    int row = i / ROW_COUNT;     // Row index
    auto btn =
        std::make_unique<LevelButton>(startx + column * offsetx,  // X-position
                                      starty + row * offsety,     // Y-position
                                      i + 1);
    // btn->set_handler([=]() { Game::get_instance().init_level(i + 1); });
    btn->set_handler([=]() { std::cout << i + 1 << std::endl; });
    levels_btns.push_back(std::move(btn));  // Level number
  }

  // Initialize the go back button
  go_back = std::make_shared<IconButton>(
      "./assets/buttons/GoBack.png", "./assets/buttons/GoBack_Hover.png", 60,
      60, StandardButton::ButtonSize::DEFAULT,
      StandardButton::ButtonType::SQUARE);
  go_back->set_handler([this]() { notify_observers(GO_BACK_SWITCH); });

  // Initialize the mute button
  mute_button = std::make_shared<MuteButton>(60, h - 60);
}

void LevelsPage::on_pause() {}
void LevelsPage::on_unpause() {}

void LevelsPage::handle_events(EventData evt) {
  for (auto& btn : levels_btns) btn->handle_events(evt);
  go_back->handle_events(evt);
  mute_button->handle_events(evt);
}

void LevelsPage::update() {}

void LevelsPage::render(std::shared_ptr<sf::RenderTarget> window) {
  for (auto& btn : levels_btns) btn->render(window);
  go_back->render(window);
  mute_button->render(window);
}
