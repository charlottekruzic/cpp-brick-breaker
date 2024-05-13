#ifndef SPEDUP_H
#define SPEDUP_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant un malus permettant d'accélérer la balle
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class SpedUp : public BonusMalus<Shape> {
 public:
  /**
   * @brief Constructeur de la classe SpedUp
   * @param game Game auquel appartient le malus
   * @param x Position x du malus
   * @param y Position y du malus
   */
  SpedUp(Game<Shape>* game, const int x, const int y);

  /**
   * @brief Appliquer l'effet du malus
   * @return void
   * @details Accélérer la balle
   */
  void applyEffect() override;
};

#include "SpedUp.hpp"
#endif  // SPEDUP_H