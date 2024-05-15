#ifndef MULTIBALL_H
#define MULTIBALL_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant un bonus permettant de générer de nouvelles balles
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class MultiBall : public BonusMalus<Shape> {
 public:
  /**
   * @brief Constructeur de la classe MultiBall
   * @param game Game auquel appartient le bonus
   * @param x Position x du bonus
   * @param y Position y du bonus
   */
  MultiBall(Game<Shape>* game, const int x, const int y);

  /**
   * @brief Appliquer l'effet du bonus
   * @details Générer de nouvelles balles
   *
   */
  void applyEffect() override;
};

#include "MultiBall.hpp"
#endif  // MULTIBALL_H