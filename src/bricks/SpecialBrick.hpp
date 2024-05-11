#include "SpecialBrick.h"

template <typename Derived>
SpecialBrick<Derived>::SpecialBrick(Game* game,
                                    std::shared_ptr<SDL_Renderer>& renderer)
    : Brick(1, game) {}

template <typename Derived>
void SpecialBrick<Derived>::renderCell(std::shared_ptr<SDL_Renderer>& renderer,
                                       int x, int y, int cellWidth,
                                       int cellHeight) {
  int padding = 1;  // Espace entre chaque case
  int size = cellWidth - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer.get(), getTexture().get(), NULL, &rect);
}

template <typename Derived>
bool SpecialBrick<Derived>::hit() {
  if (hitsLeft_ > 0) {
    hitsLeft_--;
  }
  if (hitsLeft_ == 0) {
    performAction();
    return true;
  }
  return false;
}
