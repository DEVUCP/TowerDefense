#pragma once
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "SFML/Graphics.hpp"

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
  std::shared_ptr<sf::RenderWindow> window;
  sf::Event event;
  BackgroundManager background_mng;
};
