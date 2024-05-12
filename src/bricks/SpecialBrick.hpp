#include "SpecialBrick.h"

template <class Derived, typename Shape>
SpecialBrick<Derived, Shape>::SpecialBrick(
    Game* game, std::shared_ptr<SDL_Renderer>& renderer)
    : Brick<Shape>(1, game) {}

template <class Derived, typename Shape>
SpecialBrick<Derived, Shape>::SpecialBrick(
    Game* game, std::shared_ptr<SDL_Renderer>& renderer,
    TriangleCell::Orientation orientation)
    : Brick<Shape>(1, game, orientation) {}

template <class Derived, typename Shape>
void SpecialBrick<Derived, Shape>::renderCell(
    std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int cellWidth,
    int cellHeight) {
  static_cast<Derived*>(this)->renderCell(renderer, x, y, cellWidth,
                                          cellHeight);
}

template <class Derived, typename Shape>
bool SpecialBrick<Derived, Shape>::hit() {
  if (this->hitsLeft_ > 0) {
    this->hitsLeft_--;
  }
  if (this->hitsLeft_ == 0) {
    performAction();
    return true;
  }
  return false;
}