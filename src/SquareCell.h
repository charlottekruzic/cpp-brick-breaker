#ifndef SQUARE_CELL_H
#define SQUARE_CELL_H

#include <SDL2/SDL.h>

#include <memory>

class SquareCell {
 public:
  /**
   * @brief Constructeur par défaut
   * @param size Taille du carré
   * @return void
   * @note Par défaut, la taille est de 10
   */
  SquareCell(const int size = 10);

  /**
   * @brief Récupère la taille du carré
   * @return Taille du carré
   */
  int getSize() const;

  /**
   * @brief Dessine un carré
   * @param renderer Renderer
   * @param x Position x
   * @param y Position y
   * @param cellWidth Largeur de la cellule
   * @param cellHeight Hauteur de la cellule
   * @param color Couleur du carré
   * @return void
   */
  void draw(const std::shared_ptr<SDL_Renderer>& renderer, const int x,
            const int y, const int cellWidth, const int cellHeight,
            const SDL_Color color);

 private:
  int size_;  // Dimension du carré
};

#endif  // SQUARE_CELL_H
