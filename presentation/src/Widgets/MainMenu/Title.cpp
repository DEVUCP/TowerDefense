#include "Widgets/MainMenu/Title.hpp"
#include "Utils/TextBuilder.hpp"

Title::Title() {
  TextBuilder builder;
  title_text = builder.setText("Bug Slayer")
                   .setColor(sf::Color::Yellow)
                   .setSize(200)
                   .build();
}
void Title::handle_events(sf::Event) {}

void Title::render(std::shared_ptr<sf::RenderTarget> window) {
  window->draw(title_text);
}

void Title::update() {}
