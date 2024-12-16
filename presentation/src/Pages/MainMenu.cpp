
#include "Pages/MainMenu.hpp"
#include <iostream>
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

MainMenu::MainMenu(unsigned width, unsigned height) : Page(width, height) {
  background.load_img("./assets/background/Default.png", target_width,
                      target_height);
}

void MainMenu::on_pause() {}
void MainMenu::on_unpause() {}

void MainMenu::handle_events(sf::Event) {}

void MainMenu::update() {}

void MainMenu::render(std::shared_ptr<sf::RenderTarget> window) {
  background.render(window);
}
