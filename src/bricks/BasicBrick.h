#ifndef BASICsBRICK_H
#define BASICsBRICK_H

#include <iostream>

#include "../TriangleCell.h"
#include "Brick.h"

// Classe représentant une brique basique
template <typename Shape>
class BasicBrick : public Brick<Shape> {
 public:
  BasicBrick(int strength, Game* game) : Brick<Shape>(strength, game) {
    std::cout << "création d'un basic brick SANS ORIENTATION" << std::endl;
  }  // Constructeur prenant la couleur choisie
  BasicBrick(int strength, Game* game, TriangleCell::Orientation orientation)
      : Brick<Shape>(strength, game, orientation) {
    std::cout << "création d'un basic brick avec ORIENTATION" << std::endl;
    this->shape_ = TriangleCell(orientation);
  }  // Constructeur prenant la couleur choisie
};

#endif  // BASICsBRICK_H
