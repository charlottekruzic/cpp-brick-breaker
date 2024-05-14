#ifndef CELL_H
#define CELL_H

#include <SDL2/SDL.h>

#include <memory>

#include "Colors.h"
#include "HexagonCell.h"
#include "SquareCell.h"
#include "TriangleCell.h"

/**
 * @brief Classe abstraite représentant une cellule
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Cell {
 public:
  /**
   * @brief Destructeur de la classe Cell
   */
  virtual ~Cell() {}

  /**
   * @brief Savoir si la balle doit rebondir sur la cellule
   * @return bool Vrai si la balle doit rebondir, faux sinon
   */
  virtual bool rebondir() const = 0;

  /**
   * @brief Savoir si la balle a touché la cellule et si elle doit être cassée
   * @return bool Vrai si la cellule est cassée, faux sinon
   */
  virtual bool hit() = 0;

  /**
   * @brief Afficher la cellule
   * @param renderer Renderer utilisé pour afficher la cellule
   * @param x Position en x de la cellule
   * @param y Position en y de la cellule
   * @param cellWidth Largeur de la cellule
   * @param cellHeight Hauteur de la cellule
   */
  virtual void renderCell(std::shared_ptr<SDL_Renderer>& renderer, const int x,
                          const int y, const float cellWidth,
                          const float cellHeight) = 0;

  /**
   * @brief Obtenir la couleur de la cellule
   * @return Color Couleur de la cellule
   */
  virtual Color getColor() const = 0;

  /**
   * @brief Obtenir un point de la forme de la cellule
   * @param i Indice du point
   * @return SDL_Point Point de la forme de la cellule
   */
  virtual SDL_Point getPoint(int i) = 0;
};

#endif  // CELL_H
