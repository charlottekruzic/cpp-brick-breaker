#ifndef SQUARE_CELL_H
#define SQUARE_CELL_H

#include <SDL2/SDL.h>

#include <memory>

/**
 * @brief Classe représentant une cellule carrée
 */
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
  inline int getSize() const { return size_; }

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

  /**
   * @brief Retourne un point SDL arbitraire.
   *
   * Cette méthode statique retourne un point SDL arbitraire pour une valeur
   * entière donnée.
   *
   * @param i La valeur entière pour laquelle le point SDL est retourné.
   * @return Le point SDL arbitraire correspondant à la valeur entière donnée.
   *
   */
  static SDL_Point getPoint(const int i) {
    // Retourne un SDL_Point arbitraire
    return {0, 0};  // Par exemple, (0, 0)
  }

 private:
  int size_; /**< Dimension du carré */
};

#endif  // SQUARE_CELL_H
