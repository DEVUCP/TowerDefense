#pragma once

#include "Components/SpriteSheetManager.hpp"
#include "Interfaces/Clickable.hpp"
#include "Interfaces/Widget.hpp"
#include "Map/BaseTile.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
class TileView : public Clickable, public Widget {
public:
  TileView(std::shared_ptr<BaseTile> tile);
  virtual ~TileView() = default;

  /*
   * Overrided Methods
   */
  virtual void handle_events(EventData data);
  virtual void render(RenderData);
  virtual void update(UpdateData);

  /**
   * @brief Get the tile
   */
  std::shared_ptr<BaseTile> get_tile() const;

  /**
   * @brief Set Selected
   */
  void set_selected(bool value);

protected:
  void load_sheets(const std::vector<std::string>&);

private:
  void init_selected();

protected:
  std::shared_ptr<BaseTile> tile;

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::RectangleShape shape;
  sf::Texture selected_texture;
  sf::Sprite selected_sprite;
  SpriteSheetManager selected_mng;
  bool selected;
};
