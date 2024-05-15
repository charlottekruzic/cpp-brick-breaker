#ifndef TRIANGLE_CELL_H
#define TRIANGLE_CELL_H

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <vector>

/**
 * @brief Classe représentant une cellule triangulaire
 */
class TriangleCell {
 public:
  /**
   * @brief Enumération représentant l'orientation de la cellule
   */
  enum class Orientation { UP, DOWN };

  /**
   * @brief Constructeur par défaut
   */
  TriangleCell();

  /**
   * @brief Constructeur avec orientation
   * @param orientation Orientation de la cellule
   */
  TriangleCell(Orientation orientation);

  /**
   * @brief Dessine une cellule triangulaire
   * @param renderer Renderer
   * @param x Position x
   * @param y Position y
   * @param cellWidth Largeur de la cellule
   * @param cellHeight Hauteur de la cellule
   * @param color Couleur de la cellule
   */
  void draw(const std::shared_ptr<SDL_Renderer>& renderer, const int x,
            const int y, const int cellWidth, const int cellHeight,
            const SDL_Color color);

  /**
   * @brief Récupère un point de la cellule
   * @param i Indice du point à récupérer
   * @return Point de la cellule à l'indice i
   * @note Si l'indice est invalide, retourne un point vide (0, 0)
   */
  SDL_Point getPoint(const int i) const;

 private:
  Orientation orientation_;       /**< Orientation de la cellule */
  std::vector<SDL_Point> points_; /**< Points de la cellule */

  /**
   * @brief Remplit un triangle
   * @param renderer Renderer
   * @param points Points du triangle
   */
  void fillTriangle(const std::shared_ptr<SDL_Renderer>& renderer,
                    const std::vector<SDL_Point>& points) const;
};

#endif  // TRIANGLE_CELL_H
