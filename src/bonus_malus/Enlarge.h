#ifndef ENLARGE_H
#define ENLARGE_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant un bonus permettant d'agrandir la plateforme
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Enlarge : public BonusMalus<Shape> {
 public:
  /**
   * @brief Constructeur de la classe Enlarge
   * @param game Game auquel appartient le bonus
   * @param x Position x du bonus
   * @param y Position y du bonus
   */
  Enlarge(Game<Shape>* game, const int x, const int y);

  /**
   * @brief Appliquer l'effet du bonus
   * @details Agrandir la plateforme
   *
   */
  void applyEffect() override;
};

#include "Enlarge.hpp"
#endif  // ENLARGE_H