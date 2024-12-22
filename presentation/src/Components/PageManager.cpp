#include "Components/PageManager.hpp"
#include <cassert>
#include <memory>
#include "Components/BackgroundManager.hpp"
#include "Components/PageFactory.hpp"
#include "Enums/Event.hpp"
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
  page->register_observer(self);
  page->register_observer(back_mng);
  page->on_unpause();
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
  if (pages.size()) {
    pages.top()->on_unpause();
  };
}

void PageManager::render(RenderData ren) {
  back_mng->render(ren);
  assert(pages.size());
  pages.top()->render(ren);
}

void PageManager::handle_events(EventData evt) {
  assert(pages.size());

  pages.top()->handle_events(evt);
}

void PageManager::update(UpdateData dat) {
  assert(pages.size());

  pages.top()->update(dat);
}

void PageManager::onEvent(Event evt) {
  switch (evt) {
    case Event::MENU_MENU_SWITCH:
      go_to_page(PageType::MAIN_MENU);
      break;
    case Event::LEVEL_PAGE_SWITCH:
      go_to_page(PageType::LEVELS_PAGE);
      break;
    case Event::GAME_PAGE_SWITCH:
      go_to_page(PageType::GAME_PAGE);
      break;
    case Event::GO_BACK_SWITCH:
      go_back();
      break;
    default:
      break;
  }
}
