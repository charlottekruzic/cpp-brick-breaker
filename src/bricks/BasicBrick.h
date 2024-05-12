#ifndef BASICsBRICK_H
#define BASICsBRICK_H

#include <iostream>

#include "../TriangleCell.h"
#include "Brick.h"

/**
 * @brief Classe représentant une brique classique avec une force associées
 *
 * @tparam Shape
 */
template <typename Shape>
class BasicBrick : public Brick<Shape> {
 public:
  BasicBrick(int strength, Game<Shape>* game) : Brick<Shape>(strength, game) {}
  BasicBrick(int strength, Game<Shape>* game,
             TriangleCell::Orientation orientation)
      : Brick<Shape>(strength, game, orientation) {}
};

#endif  // BASICsBRICK_H
