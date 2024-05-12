#ifndef BASICsBRICK_H
#define BASICsBRICK_H

#include "../TriangleCell.h"
#include "Brick.h"

// Classe représentant une brique basique
template <typename Shape>
class BasicBrick : public Brick<Shape> {
 public:
  BasicBrick(int strength, Game* game)
      : Brick<Shape>(strength, game) {
  }  // Constructeur prenant la couleur choisie
  BasicBrick(int strength, Game* game, TriangleCell::Orientation orientation)
      : Brick<Shape>(strength, game, orientation) {
  }  // Constructeur prenant la couleur choisie
};

#endif  // BASICsBRICK_H
