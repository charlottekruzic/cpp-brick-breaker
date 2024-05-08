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

  inline int getRows() const { return rows_; }
  inline int getCols() const { return cols_; }
  inline int getCellSize() const {
    return std::min(width_ / getCols(), height_ / getRows());
  }
  Cell* getCell(int row, int col) const;
  void hitCell(int x, int y);
  inline bool hasRemainingBricks() const { return remainingBricks_ > 0; }

 private:
  int rows_;
  int cols_;
  int width_;
  int height_;
  std::vector<std::vector<Cell*>> grid_;
  SDL_Renderer* renderer_;
  int remainingBricks_;  // Nouvel attribut pour su
};

#endif  // GRID_H
