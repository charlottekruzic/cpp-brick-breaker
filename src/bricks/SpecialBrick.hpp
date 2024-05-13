#include "SpecialBrick.h"

// Constructeurs de la classe SpecialBrick
template <class Derived, typename Shape>
SpecialBrick<Derived, Shape>::SpecialBrick(
    Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer)
    : Brick<Shape>(1, game) {}

template <class Derived, typename Shape>
SpecialBrick<Derived, Shape>::SpecialBrick(
    Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
    const TriangleCell::Orientation orientation)
    : Brick<Shape>(1, game, orientation) {}

// Afficher la brique
template <class Derived, typename Shape>
void SpecialBrick<Derived, Shape>::renderCell(
    std::shared_ptr<SDL_Renderer>& renderer, const int x, const int y,
    const float cellWidth, const float cellHeight) {
  static_cast<Derived*>(this)->renderCell(renderer, x, y, cellWidth,
                                          cellHeight);
}

// Action quand la brique est touchée
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