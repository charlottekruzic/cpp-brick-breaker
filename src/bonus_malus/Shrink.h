#ifndef SHRINK_H
#define SHRINK_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant un malus permettant de réduire la taille de la
 * plateforme
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Shrink : public BonusMalus<Shape> {
 public:
  /**
   * @brief Constructeur de la classe Shrink
   * @param game Game auquel appartient le malus
   * @param x Position x du malus
   * @param y Position y du malus
   */
  Shrink(Game<Shape>* game, const int x, const int y);

  /**
   * @brief Appliquer l'effet du malus
   * @details Réduire la taille de la plateforme
   */
  void applyEffect() override;
};

#include "Shrink.hpp"
#endif  // SHRINK_H