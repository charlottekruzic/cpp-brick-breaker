#include "MalusBonusBrick.h"

template <typename Derived>
MalusBonusBrick<Derived>::MalusBonusBrick(
    Game* game, std::shared_ptr<SDL_Renderer>& renderer)
    : Brick(1, game) {}

template <typename Derived>
void MalusBonusBrick<Derived>::renderCell(
    std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int cellSize) {
  int padding = 1;  // Espace entre chaque case
  int size = cellSize - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer.get(), getTexture().get(), NULL, &rect);
}

template <typename Derived>
bool MalusBonusBrick<Derived>::hit() {
  if (hitsLeft_ > 0) {
    hitsLeft_--;
  }
  if (hitsLeft_ == 0) {
    performAction();
    return true;
  }
  return false;
}
