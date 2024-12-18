#pragma once

#include <memory>
#include <vector>
#include "Interfaces/Observer.hpp"
class Observable {
public:
  /*
   * @brief Notify all subscribers
   */
  template <typename Event>
  void notify_observers(Event evt) const {
    for (auto& obs : observers) {
      auto typedObserver = std::static_pointer_cast<Observer<Event>>(obs);
      typedObserver->onEvent(evt);
    }
  }

public:
  /*
   * @brief Register an observer
   */
  template <typename Event>
  void register_observer(std::shared_ptr<Observer<Event>> obs) {
    observers.push_back(obs);
  }

private:
  std::vector<std::shared_ptr<IObserver>> observers;
};
