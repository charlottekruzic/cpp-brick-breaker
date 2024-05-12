#ifndef EMPTY_H
#define EMPTY_H

#include "../Cell.h"

// Classe représentant une case vide
template <typename Shape>
class Empty : public Cell<Shape> {
 public:
  Empty();
  Empty(Color color);
  Empty(TriangleCell::Orientation orientation);
  ~Empty() override;

  // Les objets ne rebondissent pas sur une case vide
  inline bool rebondir() const override { return false; }
  inline bool hit() override { return true; }
  inline Color getColor() const override { return this->color_; }

  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  float cellWidth, float cellHeight) override;
};

#include "Empty.hpp"

#endif  // EMPTY_H
