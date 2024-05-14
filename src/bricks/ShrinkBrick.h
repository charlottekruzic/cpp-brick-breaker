// SpeedChangeBrick.h
#ifndef SHRINK_BRICK_H
#define SHRINK_BRICK_H

#include "../Game.h"
#include "MalusBrick.h"

/**
 * @brief Classe représentant une brique malus qui réduit la largeur de la
 * plateforme
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class ShrinkBrick : public MalusBrick<Shape> {
 public:
  /**
   * @brief Constructeur de la classe ShrinkBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   */
  ShrinkBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer)
      : MalusBrick<Shape>(game, renderer) {}

  /**
   * @brief Constructeur de la classe ShrinkBrick avec orientation pour les
   * cases triangulaires
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param orientation Orientation de la brique
   */
  ShrinkBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
              const TriangleCell::Orientation orientation)
      : MalusBrick<Shape>(game, renderer, orientation) {}

  /**
   * @brief Appliquer l'effet du malus
   * @note Réduit la largeur de la plateforme
   */
  inline void performAction() override { this->game_->shrinkPlateformWidth(); }
};

#endif  // SHRINK_BRICK_H