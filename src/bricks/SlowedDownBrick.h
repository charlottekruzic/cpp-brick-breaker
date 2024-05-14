// SpeedChangeBrick.h
#ifndef SLOWEDDOWN_BRICK_H
#define SLOWEDDOWN_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

/**
 * @brief Classe représentant une brique bonus ralentissant la balle
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class SlowedDownBrick : public BonusBrick<Shape> {
 public:
  /**
   * @brief Constructeur de la classe SlowedDownBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   */
  SlowedDownBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer)
      : BonusBrick<Shape>(game, renderer) {}

  /**
   * @brief Constructeur de la classe SlowedDownBrick avec orientation pour les
   * cases triangulaires
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param orientation Orientation de la brique
   */
  SlowedDownBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
                  const TriangleCell::Orientation orientation)
      : BonusBrick<Shape>(game, renderer, orientation) {}

  /**
   * @brief Appliquer l'effet du bonus
   * @note Ralentit la balle
   */
  inline void performAction() override { this->game_->setBallDecelerating(); }
};

#endif  // SLOWEDDOWN_BRICK_H