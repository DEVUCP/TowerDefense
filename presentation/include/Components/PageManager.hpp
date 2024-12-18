#pragma once
#include <memory>
#include <stack>
#include "Components/BackgroundManager.hpp"
#include "Components/Page.hpp"
#include "Enums/Events/PageEvents.hpp"
#include "Enums/PageType.hpp"
#include "Interfaces/EventData.hpp"
#include "Interfaces/Observer.hpp"
#include "Interfaces/Widget.hpp"

/*
 * Invariants:
 *  - A page is always in there
 */
class PageManager : public Widget,
                    public Observer<PageEvent>,
                    public std::enable_shared_from_this<PageManager> {
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
  void go_to_page(PageType page);

  /**
   * @brief Replace the current page
   */
  void replace_page(PageType type);

  /**
   * @brief Go back a page
   */
  void go_back();

  /**
   * Overrided functions
   */
  void handle_events(EventData) override;
  void render(std::shared_ptr<sf::RenderTarget> window) override;
  void update() override;
  void onEvent(PageEvent) override;

private:
  std::stack<std::shared_ptr<Page>>
      pages;  //< A stack with all pages to support going back
  unsigned target_width;
  unsigned target_height;
  std::shared_ptr<BackgroundManager> back_mng;
};
