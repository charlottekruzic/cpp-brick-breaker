#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include "SpecialBrick.h"

/**
 * @brief Classe représentant une brique bonus
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class BonusBrick : public SpecialBrick<BonusBrick<Shape>, Shape> {
 public:
  /**
   * @brief Constructeur de la classe BonusBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer SDL
   */
  BonusBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer);

  /**
   * @brief Constructeur de la classe BonusBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer SDL
   * @param orientation Orientation de la brique utilisée pour les briques
   * triangulaires
   */
  BonusBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
             const TriangleCell::Orientation orientation);

  /**
   * @brief Obtenir la texture du malus
   * @return std::shared_ptr<SDL_Texture>& Texture du malus
   */
  static std::shared_ptr<SDL_Texture>& getTexture() { return bonus_texture_; }

  /**
   * @brief Afficher la brique
   * @param renderer Renderer SDL
   * @param x Position x de la brique
   * @param y Position y de la brique
   * @param cellWidth Largeur d'une cellule
   * @param cellHeight Hauteur d'une cellule
   */
  void renderCell(const std::shared_ptr<SDL_Renderer>& renderer, const int x,
                  const int y, const float cellWidth, const float cellHeight);

  /**
   * @brief Obtenir la couleur de la brique
   * @return Color Couleur de la brique
   */
  inline Color getColor() const override { return Color::DarkGreen; };

 private:
  static std::shared_ptr<SDL_Texture> bonus_texture_; /**< Texture du bonus */
};

#include "BonusBrick.hpp"

#endif  // BONUS_BRICK_H