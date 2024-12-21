#include "Components/PageFactory.hpp"
#include <memory>
#include "Pages/GamePage.hpp"
#include "Pages/LevelsPage.hpp"
#include "Pages/MainMenu.hpp"

PageFactory::PageFactory() { init_creators(); }

PageFactory& PageFactory::get_instance() {
  static PageFactory factory;
  return factory;
}

void PageFactory::init_creators() {
  register_creator<MainMenu>(PageType::MAIN_MENU);
  register_creator<LevelsPage>(PageType::LEVELS_PAGE);
  register_creator<GamePage>(PageType::GAME_PAGE);
}
