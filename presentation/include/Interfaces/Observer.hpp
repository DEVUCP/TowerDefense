#pragma once

#include "Enums/Event.hpp"

class Observer {
public:
  /*
   * @brief Handle when an event has been done
   */
  virtual void onEvent(Event evt) = 0;
};
