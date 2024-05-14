// SpeedChangeBrick.h
#ifndef SPEDUP_BRICK_H
#define SPEDUP_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

/**
 * @brief Classe représentant une brique malus qui accélère la balle
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class SpedUpBrick : public MalusBrick<Shape> {
 public:
  /**
   * @brief Constructeur de la classe SpedUpBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   */
  SpedUpBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer)
      : MalusBrick<Shape>(game, renderer) {}

  /**
   * @brief Constructeur de la classe SpedUpBrick avec orientation pour les
   * cases triangulaires
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param orientation Orientation de la brique
   */
  SpedUpBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
              const TriangleCell::Orientation orientation)
      : MalusBrick<Shape>(game, renderer, orientation) {}

  /**
   * @brief Appliquer l'effet du malus
   * @note Accélère la balle
   */
  inline void performAction() override { this->game_->setBallAccelerating(); }
};

#endif  // SPEDUP_BRICK_H