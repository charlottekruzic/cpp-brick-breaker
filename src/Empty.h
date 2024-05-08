#ifndef EMPTY_H
#define EMPTY_H

#include <SDL2/SDL_image.h>

#include "Cell.h"

// Classe représentant une case vide
class Empty : public Cell {
 public:
  Empty();
  // Empty(SDL_Renderer* renderer);
  ~Empty();

  bool rebondir() const override;
  bool hit() override;
  // void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth)
  // override;

 private:
  // static SDL_Texture* empty_texture_;
};

#endif  // EMPTY_H
