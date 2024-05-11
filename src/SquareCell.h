#ifndef SQUARE_CELL_H
#define SQUARE_CELL_H
#include "Cell.h"

class SquareCell {
 public:
  SquareCell(int size = 10) : size_(size) {}  // Taille par défaut de 10

  int getSize() const { return size_; }
  void draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
            int cellWidth, int cellHeight, SDL_Color color) const {
    int padding = 1;
    int size = cellWidth - 2 * padding;
    SDL_Rect rect = {x + padding, y + padding, size, size};
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &rect);
  }

 private:
  int size_;  // Dimension du carré
};

#endif  // SQUARE_CELL_H
