#include "Components/PageFactory.hpp"
#include <memory>

#include "Pages/AboutPage.hpp"
#include "Pages/GamePage.hpp"
#include "Pages/LevelsPage.hpp"
#include "Pages/LosePage.hpp"
#include "Pages/MainMenu.hpp"
#include "Pages/PausePage.hpp"
#include "Pages/WinPage.hpp"

PageFactory::PageFactory() { init_creators(); }

PageFactory& PageFactory::get_instance() {
  static PageFactory factory;
  return factory;
}

void PageFactory::init_creators() {
  register_creator<MainMenu>(PageType::MAIN_MENU);
  register_creator<LevelsPage>(PageType::LEVELS_PAGE);
  register_creator<GamePage>(PageType::GAME_PAGE);
  register_creator<AboutPage>(PageType::ABOUT_PAGE);
  register_creator<PausePage>(PageType::PAUSE_PAGE);
  register_creator<WinPage>(PageType::WIN_PAGE);
  register_creator<LosePage>(PageType::LOSE_PAGE);
}
