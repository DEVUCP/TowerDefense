#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "Interfaces/Observer.hpp"
class Observable {
public:
  /*
   * @brief Notify all subscribers
   */
  void notify_observers(Event evt) const {
    for (auto& obs : observers) {
      obs->onEvent(evt);
    }
  }

public:
  /*
   * @brief Register an observer
   */
  void register_observer(std::shared_ptr<Observer> obs) {
    observers.push_back(obs);
  }

private:
  std::vector<std::shared_ptr<Observer>> observers;
};
