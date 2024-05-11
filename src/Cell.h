#ifndef CELL_H
#define CELL_H

#include <memory>

#include "Colors.h"
#include "SquareCell.h"
#include "TriangleCell.h"

// Classe de base représentant une case du plateau
template <typename Shape>
class Cell {
 public:
  virtual ~Cell() {}

  virtual bool rebondir() const = 0;
  virtual bool hit() = 0;
  virtual void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                          int cellWidth, int cellHeight) = 0;

  virtual Color getColor() const { return color_; };

 protected:
  // constructeur accessible uniquement par les classes enfants
  Cell() : color_(Color::White) {}
  Cell(Color color) : color_(color) {}

  Color color_;
  Shape shape_;
};

#endif  // CELL_H
