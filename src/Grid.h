#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"
#include "InputParser.h"

class Grid {
 public:
  Grid(const std::string& filename, int width, int height,
       SDL_Renderer* renderer);
  ~Grid();

  void renderGrid(SDL_Renderer* renderer, int screenWidth,
                  int screenHeight) const;

  int getRows() const;
  int getCols() const;
  int getCellSize() const;
  Cell* getCell(int row, int col) const;

 private:
  int rows_;
  int cols_;
  int width_;
  int height_;
  std::vector<std::vector<Cell*>> grid_;
};

#endif  // GRID_H
