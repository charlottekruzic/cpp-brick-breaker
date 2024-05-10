#ifndef EMPTY_H
#define EMPTY_H

#include <SDL2/SDL_image.h>

#include "Cell.h"

// Classe représentant une case vide
class Empty : public Cell {
 public:
  Empty();
  Empty(Color color);
  ~Empty() override{};

  bool rebondir() const override;
  bool hit() override;
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override;

  Color getColor() const override;
};

#endif  // EMPTY_H
