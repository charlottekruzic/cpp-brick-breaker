#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL_image.h>

#include "Cell.h"

class Wall : public Cell {
 private:
  SDL_Texture* wall_texture_;

 public:
  Wall(SDL_Renderer* renderer);
  ~Wall();

  bool rebondir() const override;
  bool traverse() const override;
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;
};

#endif  // WALL_H
