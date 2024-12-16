#pragma once
#include <memory>
#include <stack>
#include "Components/Page.hpp"
#include "Components/PageFactory.hpp"
#include "Interfaces/Widget.hpp"

/*
 * Invariants:
 *  - A page is always in there
 */
class PageManager : public Widget {
public:
  /*
   * @brief Constructor
   *
   * @details Must intialize the MainMenu as the first page
   */
  PageManager(unsigned width, unsigned height);
  ~PageManager() = default;

  /**
   * @brief Go to another page
   *
   * @details The last page isn't removed, and we can go back to it
   */
  void go_to_page(std::shared_ptr<Page>);

  /**
   * @brief Replace the current page
   */
  void replace_page(std::shared_ptr<Page>);

  /**
   * @brief Go back a page
   */
  void go_back();

  /**
   * Overrided functions
   */
  void handle_events(sf::Event);
  void render(std::shared_ptr<sf::RenderTarget> window);
  void update();

private:
  std::stack<std::shared_ptr<Page>>
      pages;  //< A stack with all pages to support going back
  unsigned target_width;
  unsigned target_height;
};
