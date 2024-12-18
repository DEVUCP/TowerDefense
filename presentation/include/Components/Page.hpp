#pragma once

/*
 * An interface to all pages in the game
 */
#include "Enums/Events/PageEvents.hpp"
#include "Interfaces/EventData.hpp"
#include "Interfaces/Observable.hpp"
#include "Interfaces/Widget.hpp"

class PageManager;

class Page : public Widget, public Observable<PageEvent> {
public:
  /*
   * @brief Constructor
   */
  Page(unsigned width, unsigned height);
  /*
   * @brief Called when another page is added to the page manager
   */
  virtual void on_pause() = 0;

  /*
   * @brief Called when another page is removed from the stack and this page is
   * back
   */
  virtual void on_unpause() = 0;

  /*
   * Overrided functions
   */
  virtual void handle_events(EventData) override = 0;
  virtual void render(std::shared_ptr<sf::RenderTarget> window) override = 0;
  virtual void update() override = 0;

protected:
  unsigned target_width;
  unsigned target_height;
};
