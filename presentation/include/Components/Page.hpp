#pragma once

/*
 * An interface to all pages in the game
 */
#include "Interfaces/EventData.hpp"
#include "Interfaces/Observable.hpp"
#include "Interfaces/Widget.hpp"

class PageManager;

class Page : public Widget, public Observable {
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
  virtual void render(RenderData) override = 0;
  virtual void update(UpdateData) override = 0;

  /**
   * @brief Scale the width/height of the business to the target
   */
  float scale_width(float val);
  float scale_height(float val);
  unsigned scale_width(unsigned val);
  unsigned scale_height(unsigned val);

protected:
  unsigned target_width;
  unsigned target_height;
};
