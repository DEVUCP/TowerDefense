
#include <string>
#include <unordered_map>
#include "Components/IButton.hpp"
class StandardButton : public IButton {
public:
  enum class ButtonSize {
    LARGE,
    DEFAULT,
  };

  enum class ButtonType {
    RECT,
    SQUARE,
  };

public:
  StandardButton(unsigned x, unsigned y, ButtonSize size, ButtonType type);

protected:
  ButtonType type;
  ButtonSize size;
  static std::unordered_map<
      ButtonType,
      std::unordered_map<ButtonSize, std::pair<std::string, std::string>>>
      images;
};
