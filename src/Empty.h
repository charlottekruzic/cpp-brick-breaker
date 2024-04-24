#ifndef EMPTY_H
#define EMPTY_H

#include "Cell.h"

// Classe représentant une case vide
class Empty : public Cell {
 public:
  Empty();
  ~Empty();

  bool rebondir() const override;
  bool hit() override;
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;
};

#endif  // EMPTY_H
