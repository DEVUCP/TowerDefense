#include "Components/PageManager.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/PageFactory.hpp"
#include "Enums/Events/PageEvents.hpp"
#include "Enums/PageType.hpp"
#include "Interfaces/EventData.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

PageManager::PageManager(unsigned width, unsigned height)
    : target_width(width),
      target_height(height),
      back_mng(std::make_shared<BackgroundManager>(BackgroundManager::DEFAULT,
                                                   width, height)) {}

void PageManager::go_to_page(PageType type) {
  if (pages.size()) {
    pages.top()->on_pause();
  }
  auto page = PageFactory::get_instance().create_page(type, target_width,
                                                      target_height);
  auto self = shared_from_this();
  page->register_observer<PageEvent>(self);
  pages.push(page);
}

void PageManager::replace_page(PageType type) {
  assert(pages.size());
  go_back();
  go_to_page(type);
}

void PageManager::go_back() {
  assert(pages.size());
  pages.pop();
  std::cout << "post destruction" << std::endl;
  if (pages.size()) {
    pages.top()->on_unpause();
  };
}

void PageManager::render(std::shared_ptr<sf::RenderTarget> window) {
  back_mng->render(window);
  assert(pages.size());
  pages.top()->render(window);
}

void PageManager::handle_events(EventData evt) {
  assert(pages.size());

  pages.top()->handle_events(evt);
}

void PageManager::update() {
  assert(pages.size());

  pages.top()->update();
}

void PageManager::onEvent(PageEvent evt) {
  switch (evt) {
    case MENU_MENU_SWITCH:
      go_to_page(PageType::MAIN_MENU);
      break;
    case LEVEL_PAGE_SWITCH:
      go_to_page(PageType::LEVELS_PAGE);
      break;
    case GO_BACK_SWITCH:
      go_back();
      break;
  }
}
