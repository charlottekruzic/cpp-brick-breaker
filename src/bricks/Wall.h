#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL.h>

#include "../Cell.h"

/**
 * @brief Classe représentant un mur
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Wall : public Cell<Shape> {
 public:
  /**
   * @brief Constructeur de la classe Wall
   * @param renderer Renderer utilisé pour afficher le mur
   */
  Wall(std::shared_ptr<SDL_Renderer>& renderer);

  /**
   * @brief Constructeur de la classe Wall avec orientation pour les cases
   * triangulaires
   * @param renderer Renderer utilisé pour afficher le mur
   * @param orientation Orientation du mur
   */
  Wall(std::shared_ptr<SDL_Renderer>& renderer,
       const TriangleCell::Orientation orientation);

  /**
   * @brief Savoir si la balle doit rebondir sur le mur
   * @return bool Vrai si la balle doit rebondir, faux sinon
   * @note La balle doit rebondir sur le mur
   */
  inline bool rebondir() const override { return true; }

  /**
   * @brief Savoir si la balle a touché le mur et s'il doit être cassé
   * @return bool Faux car le mur ne peut pas être cassé
   */
  inline bool hit() override { return false; }

  /**
   * @brief Obtenir la couleur du mur
   * @return Color Couleur du mur
   */
  inline Color getColor() const override { return this->color_; }

  /**
   * @brief Afficher le mur
   * @param renderer Renderer utilisé pour afficher le mur
   * @param x Position en x du mur
   * @param y Position en y du mur
   * @param cellWidth Largeur du mur
   * @param cellHeight Hauteur du mur
   */
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, const int x,
                  const int y, const float cellWidth,
                  const float cellHeight) override;

 private:
  static std::shared_ptr<SDL_Texture> wall_texture_; /**< Texture du mur */

  /**
   * @brief Obtenir la texture du mur
   * @return std::shared_ptr<SDL_Texture>& Texture du mur
   */
  inline static std::shared_ptr<SDL_Texture>& getTexture() {
    return wall_texture_;
  }
};

#include "Wall.hpp"

#endif  // WALL_H