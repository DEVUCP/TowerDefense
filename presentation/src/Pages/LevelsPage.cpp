#include "Pages/LevelsPage.hpp"
#include <iostream>
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/IconButton.hpp"
#include "Components/TextButton.hpp"
#include "Enums/Events/PageEvents.hpp"

LevelsPage::LevelsPage(unsigned w, unsigned h) : Page(w, h) {
  // TODO: Load the level count from the business logic
  level_count = 8;  // hardcoded for now
  // levels_btns.resize(level_count);
  //
  // // Load the buttons
  // for (int i = 0; i < level_count; i++) {
  //   sf::Texture texture;
  //   if (!texture.loadFromFile("./assets/buttons/Dummy.png")) exit(1);
  //   levels_btns[i] = std::make_shared<TextButton>(std::to_string(i + 1), 100,
  //                                                 100, texture, texture);
  // }

  // Initialize the go back button
  go_back = std::make_shared<IconButton>(
      "./assets/buttons/GoBack.png", "./assets/buttons/GoBack_Hover.png", 60,
      60, Button::ButtonSize::DEFAULT, Button::ButtonType::SQUARE);
  go_back->set_handler([this]() { notify_observers(GO_BACK_SWITCH); });
}

void LevelsPage::on_pause() {}
void LevelsPage::on_unpause() {}

void LevelsPage::handle_events(EventData evt) {
  go_back->handle_events(evt);
  for (auto& btn : levels_btns) btn->handle_events(evt);
}

void LevelsPage::update() {}

void LevelsPage::render(std::shared_ptr<sf::RenderTarget> window) {
  go_back->render(window);
  for (auto& btn : levels_btns) btn->render(window);
}
