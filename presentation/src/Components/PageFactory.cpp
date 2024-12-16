#include "Components/PageFactory.hpp"
#include <memory>
#include "Pages/MainMenu.hpp"

PageFactory::PageFactory() { init_creators(); }

PageFactory& PageFactory::get_instance() {
  static PageFactory factory;
  return factory;
}

void PageFactory::init_creators() {
  register_creator<MainMenu, unsigned, unsigned>(PageType::MAIN_MENU);
}
