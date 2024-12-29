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

  /**
   * @brief Init Time
   */
  void init_time();

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

  /**
   * @brief Initialize all needed assets, info, reading from file, etc.
   */
  void init_info();

private:
  std::shared_ptr<sf::RenderWindow> window;
  sf::Event event;
  std::shared_ptr<PageManager> page_mng;
  sf::Clock clock;
  sf::Time deltaTime;
};
