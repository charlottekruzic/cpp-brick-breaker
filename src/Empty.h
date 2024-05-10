#ifndef EMPTY_H
#define EMPTY_H

#include <SDL2/SDL_image.h>

#include "Cell.h"

// Classe représentant une case vide
class Empty : public Cell {
 public:
  Empty();
  ~Empty();

  bool rebondir() const override;
  bool hit() override;
};

#endif  // EMPTY_H
