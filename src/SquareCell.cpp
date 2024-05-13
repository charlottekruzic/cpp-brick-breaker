#include "SquareCell.h"

#include <SDL2/SDL.h>

SquareCell::SquareCell(int size) : size_(size) {}

int SquareCell::getSize() const { return size_; }

void SquareCell::draw(const std::shared_ptr<SDL_Renderer>& renderer,
                      const int x, const int y, const int cellWidth,
                      const int cellHeight, const SDL_Color color) {
  int padding = 1;
  int size = cellWidth - 2 * padding;
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer.get(), &rect);
}
