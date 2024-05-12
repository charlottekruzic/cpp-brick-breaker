#ifndef SQUARE_CELL_H
#define SQUARE_CELL_H

#include <SDL2/SDL.h>

#include <memory>

class SquareCell {
 public:
  SquareCell(int size = 10);

  int getSize() const;
  void draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
            int cellWidth, int cellHeight, SDL_Color color) const;

 private:
  int size_;  // Dimension du carré
};

#endif  // SQUARE_CELL_H
