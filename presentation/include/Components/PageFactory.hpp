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
  template <typename... Args>
  std::shared_ptr<Page> create_page(PageType type, Args&&... args) {
    return creators[type](std::forward<Args>(args)...);
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

  template <typename PageClass, typename... Args>
  void register_creator(PageType type) {
    creators[type] = [](Args&&... args) {
      return std::make_shared<PageClass>(std::forward<Args>(args)...);
    };
  }

private:
  std::unordered_map<PageType,
                     std::function<std::shared_ptr<Page>(unsigned, unsigned)>>
      creators;
};
