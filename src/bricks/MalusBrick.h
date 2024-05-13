#ifndef MALUS_BRICK_H
#define MALUS_BRICK_H

#include "SpecialBrick.h"

/**
 * @brief Classe représentant une brique malus
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class MalusBrick : public SpecialBrick<MalusBrick<Shape>, Shape> {
 public:
  /**
   * @brief Constructeur de la classe MalusBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   */
  MalusBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer);

  /**
   * @brief Constructeur de la classe MalusBrick avec orientation pour les cases
   * triangulaires
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param orientation Orientation de la brique
   */
  MalusBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
             const TriangleCell::Orientation orientation);

  /**
   * @brief Obtenir la texture de la brique
   * @return std::shared_ptr<SDL_Texture>& Texture de la brique
   */
  static std::shared_ptr<SDL_Texture>& getTexture() { return malus_texture_; }

  /**
   * @brief Afficher la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param x Position en x de la brique
   * @param y Position en y de la brique
   * @param cellWidth Largeur de la brique
   * @param cellHeight Hauteur de la brique
   */
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, const int x,
                  const int y, const float cellWidth, const float cellHeight);

  /**
   * @brief Obtenir la couleur de la brique
   * @return Color Couleur de la brique
   */
  inline Color getColor() const override { return Color::MalusColor; };

 private:
  static std::shared_ptr<SDL_Texture>
      malus_texture_; /**< Texture de la brique */
};

#include "MalusBrick.hpp"

#endif  // MALUS_BRICK_H