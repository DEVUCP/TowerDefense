#pragma once

#include <memory>
#include "Interfaces/Widget.hpp"
#include "Utils/Drawable.hpp"

class View : public Widget {
public:
private:
  std::shared_ptr<Drawable> sprite;
};
