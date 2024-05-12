#ifndef EMPTY_H
#define EMPTY_H

#include <SDL2/SDL_image.h>

#include <iostream>

#include "../Cell.h"

// Classe représentant une case vide
template <typename Shape>
class Empty : public Cell<Shape> {
 public:
  Empty() : Cell<Shape>(Color::Black) {}
  Empty(Color color) : Cell<Shape>(color) {}
  Empty(TriangleCell::Orientation orientation) : Cell<Shape>(Color::Black) {
    this->shape_ = TriangleCell(orientation);
  }
  ~Empty() override{};

  bool rebondir() const override {
    return false;  // Les objets ne rebondissent pas sur une case vide
  }

  bool hit() override { return true; }
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override {
    this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                      ColorUtils::convertColor(getColor()));
  }

  Color getColor() const override { return this->color_; }
};

#endif  // EMPTY_H
