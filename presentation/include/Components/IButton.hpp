#pragma once
#include <string>
#include "Interfaces/Clickable.hpp"
#include "Interfaces/EventData.hpp"
#include "Interfaces/Widget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class IButton : public Widget, public Clickable {
public:
  /*
   * @brief Constructor
   *
   * @param x The x position of the button
   * @param y The y position of the button
   * @param size The size of the button
   * @param type The type of the button
   */
  IButton(unsigned x, unsigned y);

  /*
   * Overrided Functions
   */
  virtual void handle_events(EventData) override;
  virtual void render(RenderData) override;
  virtual void update(UpdateData) override;
  virtual void on_click() override;

protected:
  void init_image(std::string texture_path, std::string texture_path_hover);

protected:
  sf::Texture texture;
  sf::Texture texture_hover;
  sf::Sprite bg;

private:
  std::function<void(void)> handler;
  unsigned x, y;
};
