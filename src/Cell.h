#ifndef CELL_H
#define CELL_H

#include <SDL2/SDL.h>

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

  virtual Color getColor() const = 0;  //{ return color_; };

  SDL_Point getPoint(int i) { return this->shape_.getPoint(i); };

 protected:
  // constructeur accessible uniquement par les classes enfants
  Cell() : color_(Color::DEFAULT_COLOR) {}
  Cell(Color color) : color_(color) {}
  Cell(TriangleCell::Orientation orientation) : orientation_(orientation) {
    this->shape_ = TriangleCell(orientation);
  }
  Cell(Color color, TriangleCell::Orientation orientation)
      : color_(color), orientation_(orientation) {
    this->shape_ = TriangleCell(orientation);
  }

  Color color_;
  Shape shape_;
  TriangleCell::Orientation orientation_;
};

#endif  // CELL_H
