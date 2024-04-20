#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"
#include "InputParser.h"

class Grid {
 public:
  Grid(const std::string& filename, SDL_Renderer* renderer);
  ~Grid();

  void renderGrid(SDL_Renderer* renderer, int screenWidth,
                  int screenHeight) const;

 private:
  int rows_;
  int cols_;
  std::vector<std::vector<Cell*>> grid_;
};

#endif  // GRID_H
