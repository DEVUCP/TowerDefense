#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "SFML/Window/Event.hpp"

class App {
public:
  App();
  /*
   * @brief Run the game
   */
  void run();

private:
  /*
   * @brief Initliaze the window
   */
  void init_window();

  /*
   * @brief Handle all events of the game
   */
  void handle_events();

  /*
   * @brief Update the state of the game
   */
  void update();

  /*
   * @brief Render the game
   */
  void render();

private:
  std::unique_ptr<sf::RenderWindow> window;
  sf::Event event;
};
