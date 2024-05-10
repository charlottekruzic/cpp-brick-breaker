#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Cell.h"
#include "Game.h"
#include "InputParser.h"
#include "Shape.h"

class Game;

template <typename CellShape>
class Grid {
 public:
  Grid(const std::string& filename, int width, int height,
       std::shared_ptr<SDL_Renderer>& renderer, Game* game);
  ~Grid();

  void renderGrid(std::shared_ptr<SDL_Renderer>& renderer, int screenWidth,
                  int screenHeight) const;
  CellShape* getCell(int row, int col) const;
  void hitCell(int x, int y);
  inline bool hasRemainingBricks() const { return remainingBricks_ > 0; }
  inline int getRows() const { return rows_; }
  inline int getCols() const { return cols_; }
  inline int getCellSize() const {
    return std::min(width_ / getCols(), height_ / getRows());
  }

 private:
  int rows_;
  int cols_;
  int width_;
  int height_;
  Game* game_;
  std::vector<std::vector<std::shared_ptr<CellShape>>> grid_;
  std::shared_ptr<SDL_Renderer>& renderer_;
  int remainingBricks_;  // Nouvel attribut pour su
};
#endif  // GRID_H