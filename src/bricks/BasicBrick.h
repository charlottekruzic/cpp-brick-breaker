#ifndef BASICsBRICK_H
#define BASICsBRICK_H

#include <iostream>

#include "../TriangleCell.h"
#include "Brick.h"

/**
 * @brief Classe représentant une brique classique avec une force associées
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class BasicBrick : public Brick<Shape> {
 public:
  /**
   * @brief Constructeur de la classe BasicBrick
   * @param strength Force de la brique
   * @param game Game auquel appartient la brique
   */
  BasicBrick(const int strength, Game<Shape>* game)
      : Brick<Shape>(strength, game) {}

  /**
   * @brief Constructeur de la classe BasicBrick
   * @param strength Force de la brique
   * @param game Game auquel appartient la brique
   * @param orientation Orientation de la brique
   */
  BasicBrick(const int strength, Game<Shape>* game,
             const TriangleCell::Orientation orientation)
      : Brick<Shape>(strength, game, orientation) {}
};

#endif  // BASICsBRICK_H
