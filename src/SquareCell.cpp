#include <SDL2/SDL.h>

#include "SquareCell.h"

SquareCell::SquareCell(int size) : size_(size) {}

int SquareCell::getSize() const { return size_; }

void SquareCell::draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                      int cellWidth, int cellHeight, SDL_Color color) const {
  int padding = 1;
  int size = cellWidth - 2 * padding;
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer.get(), &rect);
}
