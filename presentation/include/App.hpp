#pragma once
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/PageManager.hpp"
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
   * @brief Initialize the page manager
   */
  void init_page_manager();

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
  std::shared_ptr<PageManager> page_mng;
};
