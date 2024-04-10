#ifndef WALL_H
#define WALL_H

#include "Cell.h"

class Wall : public Cell {
 public:
  Wall();
  ~Wall();

  bool rebondir() const override;
  bool traverse() const override;
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;
};

#endif  // WALL_H
