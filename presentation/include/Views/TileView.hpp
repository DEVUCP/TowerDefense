#pragma once

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

protected:
  void load_sheets(const std::vector<std::string>&);

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::RectangleShape shape;
  std::shared_ptr<BaseTile> tile;
};
