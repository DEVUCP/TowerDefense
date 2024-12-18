#pragma once

#include <string>

/*
 * @brief An observer to an Event
 */
template <typename Event>
class Observer {
public:
  /*
   * @brief Handle when an event has been done
   */
  virtual void onEvent(Event evt) = 0;
};
