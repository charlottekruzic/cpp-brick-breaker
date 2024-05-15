#ifndef HEXAGON_CELL_H
#define HEXAGON_CELL_H

#include <SDL2/SDL.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
/**
 * @brief Classe représentant une cellule hexagonale
 */
class HexagonCell {
 public:
  /**
   * @brief Constructeur par défaut
   */
  HexagonCell();

  /**
   * @brief Dessine une cellule hexagonale
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
  std::vector<SDL_Point> points_; /**< Points de la cellule */

  /**
   * @brief Remplit un hexagone
   * @param renderer Renderer
   * @param points Points de l'hexagone
   */
  void fillHexagon(const std::shared_ptr<SDL_Renderer> renderer,
                   const std::vector<SDL_Point>& points) const;
};

#endif  // HEXAGON_CELL_H