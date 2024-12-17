#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include "Components/Page.hpp"
#include "Enums/PageType.hpp"
class PageFactory {
public:
  // remove copying
  PageFactory(const PageFactory&) = delete;
  PageFactory& operator=(const PageFactory&) = delete;

  /*
   * @brief Get the instance
   */
  static PageFactory& get_instance();

  /*
   * @brief Create a page
   */
  std::shared_ptr<Page> create_page(PageType type, unsigned x, unsigned y) {
    return creators[type](x, y);
  }

private:
  /*
   * @brief Constructor
   *
   * @details Initlaize all creators
   */
  PageFactory();

  /*
   * @brief Initialize all page creators
   */
  void init_creators();

  template <typename PageClass>
  void register_creator(PageType type) {
    creators[type] = [](unsigned x, unsigned y) {
      return std::make_shared<PageClass>(x, y);
    };
  }

private:
  std::unordered_map<PageType,
                     std::function<std::shared_ptr<Page>(unsigned, unsigned)>>
      creators;
};
