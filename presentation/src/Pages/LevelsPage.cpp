#include "Pages/LevelsPage.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "Components/BackgroundManager.hpp"
#include "Components/IconButton.hpp"
#include "Components/LevelButton.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Events/PageEvents.hpp"

LevelsPage::LevelsPage(unsigned w, unsigned h) : Page(w, h) {
  level_count = 8;  // hardcoded for now

  const int ROW_COUNT = 5;                 // 5 levels per row
  const int startx = 300, starty = 200;    // Starting position
  const int offsetx = 300, offsety = 200;  // Spacing between buttons
  // Load the buttons
  for (int i = 0; i < level_count; i++) {
    int column = i % ROW_COUNT;  // Column index (0 to 4)
    int row = i / ROW_COUNT;     // Row index
    levels_btns.push_back(
        std::make_unique<LevelButton>(startx + column * offsetx,  // X-position
                                      starty + row * offsety,     // Y-position
                                      i + 1));  // Level number
  }

  // Initialize the go back button
  go_back = std::make_shared<IconButton>(
      "./assets/buttons/GoBack.png", "./assets/buttons/GoBack_Hover.png", 60,
      60, StandardButton::ButtonSize::DEFAULT,
      StandardButton::ButtonType::SQUARE);
  go_back->set_handler([this]() { notify_observers(GO_BACK_SWITCH); });
}

void LevelsPage::on_pause() {}
void LevelsPage::on_unpause() {}

void LevelsPage::handle_events(EventData evt) {
  for (auto& btn : levels_btns) btn->handle_events(evt);
  go_back->handle_events(evt);
}

void LevelsPage::update() {}

void LevelsPage::render(std::shared_ptr<sf::RenderTarget> window) {
  go_back->render(window);
  for (auto& btn : levels_btns) btn->render(window);
}
