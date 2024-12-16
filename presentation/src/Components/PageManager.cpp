#include "Components/PageManager.hpp"
#include <cassert>
#include <iostream>
#include <memory>
#include "Components/PageFactory.hpp"
#include "Enums/PageType.hpp"
#include "Pages/MainMenu.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"

PageManager::PageManager(unsigned width, unsigned height)
    : target_width(width), target_height(height) {
  go_to_page(PageFactory::get_instance().create_page(PageType::MAIN_MENU, width,
                                                     height));
}

void PageManager::go_to_page(std::shared_ptr<Page> page) { pages.push(page); }

void PageManager::replace_page(std::shared_ptr<Page> page) {
  assert(pages.size());
  go_back();
  go_to_page(page);
}

void PageManager::go_back() {
  assert(pages.size() > 1);
  pages.pop();
}

void PageManager::render(std::shared_ptr<sf::RenderTarget> window) {
  assert(pages.size());

  pages.top()->render(window);
}

void PageManager::handle_events(sf::Event event) {
  assert(pages.size());

  pages.top()->handle_events(event);
}

void PageManager::update() {
  assert(pages.size());

  pages.top()->update();
}
