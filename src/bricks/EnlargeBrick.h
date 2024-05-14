// SpeedChangeBrick.h
#ifndef ENLARGE_BRICK_H
#define ENLARGE_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

/**
 * @brief Classe représentant une brique bonus qui augmente la largeur de la
 * plateforme
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class EnlargeBrick : public BonusBrick<Shape> {
 public:
  /**
   * @brief Constructeur de la classe EnlargeBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   */
  EnlargeBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer)
      : BonusBrick<Shape>(game, renderer) {}

  /**
   * @brief Constructeur de la classe EnlargeBrick avec orientation pour les
   * cases triangulaires
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param orientation Orientation de la briq
   */
  EnlargeBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
               const TriangleCell::Orientation orientation)
      : BonusBrick<Shape>(game, renderer, orientation) {}

  /**
   * @brief Appliquer l'effet du bonus
   * @note Augmente la largeur de la plateforme
   */
  inline void performAction() override { this->game_->enlargePlateformWidth(); }
};

#endif  // ENLARGE_BRICK_H