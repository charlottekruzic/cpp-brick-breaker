#ifndef EMPTY_H
#define EMPTY_H

#include "../Cell.h"

/**
 * @brief Classe représentant une case vide
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Empty : public Cell<Shape> {
 public:
  /**
   * @brief Constructeur par défaut de la classe Empty
   */
  Empty();

  /**
   * @brief Constructeur de la classe Empty
   * @param color Couleur de la case vide
   */
  Empty(const Color color);

  /**
   * @brief Constructeur de la classe Empty avec orientation pour les cases
   * triangulaires
   * @param orientation Orientation de la case
   */
  Empty(const TriangleCell::Orientation orientation);

  /**
   * @brief Destructeur de la classe Empty
   */
  ~Empty() override;

  /**
   * @brief Savoir si la balle rebondit sur la case vide
   * @return bool Retourne false
   * @note Les balles ne rebondissent pas sur une case vide
   */
  inline bool rebondir() const override { return false; }

  /**
   * @brief Action quand la balle touche la case vide
   * @return bool Retourne false
   * @note La briques ne peut pas être touchée
   */
  inline bool hit() override { return false; }

  /**
   * @brief Obtenir la couleur de la case vide
   * @return Color Couleur de la case vide
   * @note Noir par défaut
   */
  inline Color getColor() const override { return this->color_; }

  /**
   * @brief Afficher la case vide
   * @param renderer Renderer SDL
   * @param x Position x de la case vide
   * @param y Position y de la case vide
   * @param cellWidth Largeur d'une cellule
   * @param cellHeight Hauteur d'une cellule
   * @return void
   */
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, const int x,
                  const int y, const float cellWidth,
                  const float cellHeight) override;

  /**
   * @brief Obtenir un point de la forme de la case vide
   * @param i Indice du point
   * @return SDL_Point Point de la forme de la case vide
   */
  inline SDL_Point getPoint(int i) override { return shape_.getPoint(i); };

 private:
  Color color_;                           /**< Couleur de la cellule */
  Shape shape_;                           /**< Forme de la cellule */
  TriangleCell::Orientation orientation_; /**< Orientation de la cellule */
};

#include "Empty.hpp"

#endif  // EMPTY_H
