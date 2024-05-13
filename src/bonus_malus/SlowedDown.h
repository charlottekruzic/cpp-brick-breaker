#ifndef SLOWEDDOWN_H
#define SLOWEDDOWN_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant un bonus permettant de ralentir la balle
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class SlowedDown : public BonusMalus<Shape> {
 public:
  /**
   * @brief Constructeur de la classe SlowedDown
   * @param game Game auquel appartient le bonus
   * @param x Position x du bonus
   * @param y Position y du bonus
   */
  SlowedDown(Game<Shape>* game, const int x, const int y);

  /**
   * @brief Appliquer l'effet du bonus
   * @return void
   * @details Ralentir la balle
   */
  void applyEffect() override;
};

#include "SlowedDown.hpp"
#endif  // SLOWEDDOWN_H