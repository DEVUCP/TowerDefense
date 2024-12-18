#pragma once

#include <string>

class IObserver {
public:
  ~IObserver() = default;
};
/*
 * @brief An observer to an Event
 */
template <typename Event>
class Observer : public IObserver {
public:
  /*
   * @brief Handle when an event has been done
   */
  virtual void onEvent(Event evt) = 0;
};
